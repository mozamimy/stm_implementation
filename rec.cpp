#include "rec.h"

Rec::Rec()
{
    status = Status(Null, 0);
    stable = true;
    version = 1;
    allWritten = 0;
    size = 0;
    oldValues = 0;
    add = 0;
}
