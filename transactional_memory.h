#ifndef TRANSACTIONAL_MEMORY_H
#define TRANSACTIONAL_MEMORY_H

#include "rec.h"

class TransactionalMemory
{
private:
    int*  memory;
    Rec** ownerships;
    Rec*  recs;

public:
    TransactionalMemory(int memorySize, int processCount);
    ~TransactionalMemory();
};

#endif // TRANSACTIONAL_MEMORY_H
