#include "sqlrepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>

bool SqlRepository::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("task_manager.db");
    if (!db.open()) return false;

    QSqlQuery query;
    return query.exec("CREATE TABLE IF NOT EXISTS task ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "description TEXT, "
                      "deadline TEXT NOT NULL, "
                      "priority INTEGER DEFAULT 2, "
                      "is_completed INTEGER DEFAULT 0, "
                      "create_time TEXT NOT NULL)");
}
