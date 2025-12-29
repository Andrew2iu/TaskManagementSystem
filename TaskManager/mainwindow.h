#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QNetworkReply>
#include <QThread>
#include "reminderworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // mainwindow.h

private slots:
    void on_addTaskBtn_clicked();
    void on_deleteTaskBtn_clicked();
    void on_exportBtn_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void handleReminder(const QString &name, const QString &time);

    // 补齐这一行声明，用于接收网络请求结果
    void onNetworkReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxyModel;
    QThread *reminderThread;
    ReminderWorker *worker;
};
#endif
