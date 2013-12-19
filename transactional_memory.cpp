#include "transactional_memory.h"
#include "status.h"

TransactionalMemory::TransactionalMemory(int memorySize, int _processCount)
{
    memory = new int[memorySize];
    ownerships = new Rec*[memorySize];
    processCount = _processCount;

    recs = new Rec*[_processCount];
    for (int i = 0; i < _processCount; i++)
    {
        recs[i] = new Rec();
    }
}

TransactionalMemory::~TransactionalMemory()
{
    delete[] memory;
    delete[] ownerships;

    for (int i = 0; i < processCount; i++) {
        delete recs[i];
    }
    delete[] recs;
}

TransactionStatus TransactionalMemory::startTransaction(int** dataSet, int dataSetSize, int recIndex)
{
    Rec* rec_i = recs[recIndex];

    initialize(rec_i, dataSet, dataSetSize);
    rec_i->stable = true;
    transaction(rec_i, rec_i->version, true);
    rec_i->stable = false;
    rec_i->version++;

    if (rec_i->status.first == Success)
    {
        return (TransactionStatus(Success, rec_i->oldValues));
    }
    else
    {
        return (TransactionStatus(Failure, 0));
    }
}

void TransactionalMemory::initialize(Rec *rec, int **dataSet, int dataSetSize)
{
    rec->status = Status(Null, 0);
    rec->allWritten = 0;
    rec->size = dataSetSize;

    for (int j = 0; j < dataSetSize; j++)
    {
        rec->add[j] = dataSet[j];
        rec->oldValues[j] = 0;
    }
}

void TransactionalMemory::transaction(Rec *rec, int version, bool isInitiator)
{

}
