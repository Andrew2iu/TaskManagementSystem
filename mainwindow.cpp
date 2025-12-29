#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlrepository.h"
#include "fileexporter.h"
#include <QMessageBox>
#include <QDateTime>
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 数据库初始化校验
    if (!SqlRepository::initDatabase()) {
        QMessageBox::critical(this, "致命错误",
                              "数据库加载失败，程序将无法正常工作。");
    }

    // 2. 模型设置
    model = new QSqlTableModel(this, QSqlDatabase::database(SqlRepository::MAIN_CONN));
    model->setTable("task");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 3. UI 初始化：禁用右侧面板（直到用户点击列表）
    ui->editPanel->setEnabled(false);
    ui->editPriority->addItems({"高", "中", "低"});
    ui->sortComboBox->addItems({"按优先级排序", "按创建时间排序"});

    updateListView();

    // 4. 信号连接
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &MainWindow::updateListView);

    // 5. 后台提醒线程
    reminderThread = new QThread(this);
    worker = new ReminderWorker();
    worker->moveToThread(reminderThread);
    connect(reminderThread, &QThread::started, worker, &ReminderWorker::process);
    connect(worker, &ReminderWorker::reminderSignal, this, &MainWindow::handleReminder);
    reminderThread->start();

    // 6. 网络同步北京时间
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
    manager->get(QNetworkRequest(QUrl("http://worldtimeapi.org/api/timezone/Asia/Shanghai")));
}

void MainWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QString dt = doc.object().value("datetime").toString().mid(0, 19).replace("T", " ");
        ui->statusBar->showMessage("在线时间同步: " + dt);
    }
    reply->deleteLater();
}

void MainWindow::updateListView()
{
    ui->listWidget->clear();
    // 排序逻辑
    if (ui->sortComboBox->currentIndex() == 0) model->setSort(4, Qt::AscendingOrder);
    else model->setSort(6, Qt::DescendingOrder);

    model->select();
    QString filter = ui->searchLineEdit->text();

    for (int i = 0; i < model->rowCount(); ++i) {
        QString name = model->index(i, 1).data().toString();
        int prio = model->index(i, 4).data().toInt();
        int isDone = model->index(i, 5).data().toInt();

        if (!filter.isEmpty() && !name.contains(filter, Qt::CaseInsensitive)) continue;

        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::UserRole, i);

        // 视觉逻辑：已完成则灰色斜体，未完成则按优先级变色
        if (isDone) {
            item->setText("[已完成] " + name);
            item->setForeground(Qt::gray);
            QFont font = item->font();
            font.setItalic(true);
            item->setFont(font);
        } else {
            item->setText(name);
            if (prio == 0) item->setForeground(QColor("#e74c3c"));      // 高：红
            else if (prio == 1) item->setForeground(QColor("#f39c12")); // 中：橙
            else item->setForeground(QColor("#27ae60"));                // 低：绿
        }
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->editPanel->setEnabled(true); // 激活面板
    int row = item->data(Qt::UserRole).toInt();

    ui->editName->setText(model->index(row, 1).data().toString());
    ui->editDesc->setPlainText(model->index(row, 2).data().toString());
    ui->editDeadline->setDateTime(QDateTime::fromString(model->index(row, 3).data().toString(),
                                                        "yyyy-MM-dd HH:mm"));
    ui->editPriority->setCurrentIndex(model->index(row, 4).data().toInt());
    ui->checkCompleted->setChecked(model->index(row, 5).data().toInt() == 1);
}

void MainWindow::on_saveEditBtn_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (!item) return;

    int row = item->data(Qt::UserRole).toInt();
    model->setData(model->index(row, 1), ui->editName->text());
    model->setData(model->index(row, 2), ui->editDesc->toPlainText());
    model->setData(model->index(row, 3), ui->editDeadline->dateTime().toString("yyyy-MM-dd HH:mm"));
    model->setData(model->index(row, 4), ui->editPriority->currentIndex());
    model->setData(model->index(row, 5), ui->checkCompleted->isChecked() ? 1 : 0);

    if (model->submitAll()) {
        QMessageBox::information(this, "成功", "任务已更新");
        updateListView();
    }
}

void MainWindow::on_addTaskBtn_clicked()
{
    QSqlRecord rec = model->record();
    rec.setValue("name", "新任务");
    rec.setValue("deadline", QDateTime::currentDateTime().addDays(1).toString("yyyy-MM-dd HH:mm"));
    rec.setValue("priority", 1);
    rec.setValue("is_completed", 0);
    rec.setValue("create_time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm"));

    if (model->insertRecord(-1, rec)) {
        model->submitAll();
        updateListView();
    }
}

void MainWindow::on_deleteTaskBtn_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (!item) return;

    if (QMessageBox::question(this, "确认", "确定删除？") == QMessageBox::Yes) {
        model->removeRow(item->data(Qt::UserRole).toInt());
        model->submitAll();
        updateListView();
        ui->editPanel->setEnabled(false);
    }
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    updateListView();
}
void MainWindow::on_exportBtn_clicked()
{
    exportToExcel(model);
}
void MainWindow::handleReminder(const QString &n, const QString &t)
{
    QMessageBox::information(this, "提醒", n + " 到期了！");
}

MainWindow::~MainWindow()
{
    reminderThread->quit();
    reminderThread->wait();
    delete ui;
}
