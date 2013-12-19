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
    transaction(rec_i, rec_i->version, true, dataSetSize);
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

void TransactionalMemory::transaction(Rec *rec, int version, bool isInitiator, int dataSetSize)
{
    acquireOwnerships(rec, version);

    Status status = ll_status(rec->status);

    if (status.first == Null)
    {
        if (version != rec->version) return;
        sc_status(rec->status, Status(Success, 0));
    }

    status = ll_status(rec->status);

    if (status.first == Success)
    {
        agreeOldValues(rec, version);

        int* newValues = increment(rec->oldValues, dataSetSize);

        updateMemory(rec, version, newValues);
        releaseOwnerShips(rec, version);
    }
    else
    {
        releaseOwnerShips(rec, version);

        if (isInitiator)
        {

        }
        else
        {

        }
    }
}

void TransactionalMemory::acquireOwnerships(Rec *rec, int version)
{

}

void TransactionalMemory::agreeOldValues(Rec *rec, int version)
{

}

void TransactionalMemory::updateMemory(Rec *rec, int version, int *newValues)
{

}

void TransactionalMemory::releaseOwnerShips(Rec *rec, int version)
{

}

// LL/SC
Status TransactionalMemory::ll_status(Status status)
{

}

bool TransactionalMemory::sc_status(Status target, Status status)
{

}

// CalcNewValues
int* TransactionalMemory::increment(int **oldValues, int dataSetSize)
{
    int* newValues = new int[dataSetSize];

    for (int i = 0; i < dataSetSize; i++)
    {
        newValues[i] = *(oldValues[i]) + 1;
    }

    return newValues;
}
