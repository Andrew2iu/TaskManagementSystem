#ifndef SQLREPOSITORY_H
#define SQLREPOSITORY_H

#include <QString>

class SqlRepository
{
public:
    static bool initDatabase();
    // 增加这一行声明，解决 "is not a member of" 错误
    static const QString MAIN_CONN;
};
#endif
