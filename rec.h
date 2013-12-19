#ifndef REC_H
#define REC_H

#include "status.h"

class Rec
{
public:
    Status status;
    bool stable;
    int version;
    bool* allWritten;
    int size;
    int** oldValues;
    int** add;

    Rec();
};

#endif // REC_H
