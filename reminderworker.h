#ifndef REMINDERWORKER_H
#define REMINDERWORKER_H

#include <QObject>

class ReminderWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReminderWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void process(); // 线程执行函数
    1
signals:
    void reminderSignal(const QString &name, const QString &time); // 提醒信号
};

#endif // REMINDERWORKER_H
