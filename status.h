#ifndef STATUS_H
#define STATUS_H

#include <utility>

enum _status {Success, Failure, Null};
typedef std::pair<_status, int> Status;

#endif // STATUS_H
