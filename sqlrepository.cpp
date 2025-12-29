#include "sqlrepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// 在此处初始化静态变量
const QString SqlRepository::MAIN_CONN = "main_task_connection";

bool SqlRepository::initDatabase()
{
    // 使用指定的连接名
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", MAIN_CONN);
    db.setDatabaseName("task_manager.db");
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    return query.exec("CREATE TABLE IF NOT EXISTS task ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "description TEXT, "
                      "deadline TEXT NOT NULL, "
                      "priority INTEGER DEFAULT 2, "
                      "is_completed INTEGER DEFAULT 0, "
                      "create_time TEXT NOT NULL)");
}
