#include "reminderworker.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QThread>
#include <QVariant> // 修复 incomplete type QVariant

void ReminderWorker::process()
{
    // 为子线程建立独立数据库连接
    QSqlDatabase db;
    if (QSqlDatabase::contains("reminder_connection")) {
        db = QSqlDatabase::database("reminder_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", "reminder_connection");
        db.setDatabaseName("task_manager.db");
    }
    if (!db.open()) return;

    while (true) {
        QSqlQuery query(db);
        query.exec("SELECT name, deadline FROM task WHERE is_completed = 0");
        QDateTime now = QDateTime::currentDateTime();
        while (query.next()) {
            QString name = query.value(0).toString();
            QDateTime dt = QDateTime::fromString(query.value(1).toString(), "yyyy-MM-dd HH:mm");
            if (dt.isValid() && qAbs(now.secsTo(dt)) < 60) {
                emit reminderSignal(name, query.value(1).toString());
            }
        }
        QThread::msleep(30000);
    }
}
