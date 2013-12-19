#ifndef STATUS_H
#define STATUS_H

#include <utility>

enum Condition {Success, Failure, Null};
typedef std::pair<Condition, int> Status;
typedef std::pair<Condition, int**> TransactionStatus;

#endif // STATUS_H
