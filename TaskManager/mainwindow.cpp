#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlrepository.h"
#include "fileexporter.h"
#include <QMessageBox>
#include <QDateTime>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SqlRepository::initDatabase();

    model = new QSqlTableModel(this);
    model->setTable("task");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(1); // 搜索第二列(name)

    ui->tableView->setModel(proxyModel);
    ui->tableView->hideColumn(0);

    reminderThread = new QThread(this);
    worker = new ReminderWorker();
    worker->moveToThread(reminderThread);
    connect(reminderThread, &QThread::started, worker, &ReminderWorker::process);
    connect(worker, &ReminderWorker::reminderSignal, this, &MainWindow::handleReminder);
    reminderThread->start();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    proxyModel->setFilterFixedString(text);
}


// mainwindow.cpp 中的 onNetworkReply 函数内
void MainWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // ui->statusbar->showMessage("..."); // 注释掉这一行
        qDebug() << "网络连接成功";
    } else {
        qDebug() << "网络连接失败";
    }
    reply->deleteLater();
}

void MainWindow::on_addTaskBtn_clicked()
{
    QSqlRecord rec = model->record();
    rec.setValue("name", "新任务");
    rec.setValue("deadline", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
    rec.setValue("create_time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));
    model->insertRecord(-1, rec);
    model->submitAll();
    model->select();
}

void MainWindow::on_exportBtn_clicked()
{
    exportToExcel(model);
}
void MainWindow::on_deleteTaskBtn_clicked()
{
    // 1. 获取当前选中的行索引
    int curRow = ui->tableView->currentIndex().row();

    // 2. 检查用户是否选中了行，防止空操作导致程序异常
    if (curRow < 0) {
        QMessageBox::warning(this, "提示", "请先在表格中选择要删除的任务行");
        return;
    }

    // 3. 弹出二次确认框，符合异常处理与用户友好设计 [cite: 32]
    if (QMessageBox::question(this, "确认删除",
                              "确定要永久删除此任务吗？") == QMessageBox::Yes) {
        // 4. 从代理模型中移除该行（如果你使用了 ProxyModel）
        proxyModel->removeRow(curRow);

        // 5. 提交更改并刷新，解决报告 3.4.3 中提到的“数据不刷新”问题
        model->submitAll();
        model->select();
    }
}
void MainWindow::handleReminder(const QString &name, const QString &time)
{
    QMessageBox::information(this, "提醒", name + " 到期了！");
}

MainWindow::~MainWindow()
{
    reminderThread->quit();
    reminderThread->wait();
    delete ui;
}
