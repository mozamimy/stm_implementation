#ifndef TRANSACTIONAL_MEMORY_H
#define TRANSACTIONAL_MEMORY_H

#include "rec.h"
#include "status.h"

class TransactionalMemory
{
private:
    int*  memory;
    Rec** ownerships;
    Rec** recs;
    int processCount;

    void initialize(Rec* rec, int** dataSet, int dataSetSize);
    void transaction(Rec* rec, int version, bool isInitiator);


public:
    TransactionalMemory(int memorySize, int processCount);
    TransactionStatus startTransaction(int** dataSet, int dataSetSize, int recIndex);
    ~TransactionalMemory();
};

#endif // TRANSACTIONAL_MEMORY_H
