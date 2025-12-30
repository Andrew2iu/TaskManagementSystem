#include "reminderworker.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QThread>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

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

    if (!db.open()) {
        qDebug() << "提醒线程数据库打开失败:" << db.lastError().text();
        return;
    }

    // 用于记录已经提醒过的任务，防止重复弹窗（仅在程序运行期间有效）
    QStringList notifiedTasks;

    while (true) {
        QSqlQuery query(db);
        // 查询未完成的任务
        if (!query.exec("SELECT name, deadline FROM task WHERE is_completed = 0")) {
            qDebug() << "查询失败:" << query.lastError().text();
        }

        QDateTime now = QDateTime::currentDateTime();

        while (query.next()) {
            QString name = query.value(0).toString();
            QString deadlineStr = query.value(1).toString();
            QDateTime dt = QDateTime::fromString(deadlineStr, "yyyy-MM-dd HH:mm");

            // 修改匹配逻辑：只要当前时间 超过或等于 截止时间
            if (dt.isValid() && now >= dt) {
                // 检查是否已经提醒过，避免每30秒弹窗一次
                if (!notifiedTasks.contains(name + deadlineStr)) {
                    qDebug() << "触发提醒:" << name;
                    emit reminderSignal(name, deadlineStr);
                    notifiedTasks.append(name + deadlineStr);
                }
            }
        }

        // 为了方便测试，建议将休眠时间临时缩短（如 5000ms），正常使用建议 30000ms
        QThread::msleep(5000);
    }
}
