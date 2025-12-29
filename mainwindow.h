#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QListWidget>
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

private slots:
    void on_addTaskBtn_clicked();
    void on_deleteTaskBtn_clicked();
    void on_exportBtn_clicked();
    void on_saveEditBtn_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void onNetworkReply(QNetworkReply *reply);
    void handleReminder(const QString &name, const QString &time);
    void updateListView();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QThread *reminderThread;
    ReminderWorker *worker;
};
#endif
