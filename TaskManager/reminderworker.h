#ifndef REMINDERWORKER_H
#define REMINDERWORKER_H
#include <QObject>

class ReminderWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReminderWorker(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    void process();
signals:
    void reminderSignal(const QString &name, const QString &time);
};
#endif
