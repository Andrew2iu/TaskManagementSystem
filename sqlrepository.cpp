#include "sqlrepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

const QString SqlRepository::MAIN_CONN = "main_task_connection";

bool SqlRepository::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", MAIN_CONN);
    db.setDatabaseName("task_manager.db");
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    // 增加 category 字段，默认为 '默认'
    return query.exec("CREATE TABLE IF NOT EXISTS task ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "description TEXT, "
                      "deadline TEXT NOT NULL, "
                      "priority INTEGER DEFAULT 2, "
                      "is_completed INTEGER DEFAULT 0, "
                      "create_time TEXT NOT NULL, "
                      "category TEXT DEFAULT '默认')");
}
