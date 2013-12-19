#include "transactional_memory.h"

TransactionalMemory::TransactionalMemory(int memorySize, int processCount)
{
    memory = new int[memorySize];
    ownerships = new Rec*[memorySize];
    recs = new Rec[processCount];
}

TransactionalMemory::~TransactionalMemory()
{
    delete[] memory;
    delete[] ownerships;
    delete[] recs;
}
