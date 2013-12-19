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
    void transaction(Rec* rec, int version, bool isInitiator, int dataSetSize);
    void acquireOwnerships(Rec* rec, int version);
    void agreeOldValues(Rec* rec, int version);
    void updateMemory(Rec* rec, int version, int* newValues);
    void releaseOwnerShips(Rec* rec, int version);

    // LL/SC
    Status ll_status(Status status);
    bool sc_status(Status target, Status status);

    // CalsNewValues
    int* increment(int** oldValues, int dataSetSize);


public:
    TransactionalMemory(int memorySize, int processCount);
    TransactionStatus startTransaction(int** dataSet, int dataSetSize, int recIndex);
    ~TransactionalMemory();
};

#endif // TRANSACTIONAL_MEMORY_H
