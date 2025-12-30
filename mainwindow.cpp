#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlrepository.h"
#include "fileexporter.h"
#include <QMessageBox>
#include <QDateTime>
#include <QSqlRecord>
#include <QSqlError>
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

    // 2. 模型设置 (使用静态连接名)
    model = new QSqlTableModel(this, QSqlDatabase::database(SqlRepository::MAIN_CONN));
    model->setTable("task");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 3. UI 初始化
    ui->editPanel->setEnabled(false); // 默认禁用右侧面板

    // 初始化优先级列表
    ui->editPriority->clear();
    ui->editPriority->addItems({"高", "中", "低"});

    // 初始化排序列表
    ui->sortComboBox->clear();
    ui->sortComboBox->addItems({"按优先级排序", "按创建时间排序"});

    // 初始化分类列表 (确保 UI 中有名为 editCategory 和 filterCategoryCombo 的 QComboBox)
    QStringList categories = {"默认", "工作", "生活", "学习", "其他"};
    ui->editCategory->clear();
    ui->editCategory->addItems(categories);

    ui->filterCategoryCombo->clear();
    ui->filterCategoryCombo->addItem("全部分类");
    ui->filterCategoryCombo->addItems(categories);

    updateListView();

    // 4. 信号连接
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &MainWindow::updateListView);
    connect(ui->filterCategoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &MainWindow::updateListView);

    // 5. 后台提醒线程初始化
    reminderThread = new QThread(this);
    worker = new ReminderWorker();
    worker->moveToThread(reminderThread);

    // 连接线程启动信号与提醒逻辑
    connect(reminderThread, &QThread::started, worker, &ReminderWorker::process);
    // 连接提醒信号到主界面处理函数
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

    // 排序逻辑：0 为优先级，1 为创建时间
    if (ui->sortComboBox->currentIndex() == 0)
        model->setSort(4, Qt::AscendingOrder); // priority 列
    else
        model->setSort(6, Qt::DescendingOrder); // create_time 列

    model->select();

    QString nameFilter = ui->searchLineEdit->text();
    QString catFilter = ui->filterCategoryCombo->currentText();

    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord rec = model->record(i);
        QString name = rec.value("name").toString();
        QString category = rec.value("category").toString();
        int prio = rec.value("priority").toInt();
        int isDone = rec.value("is_completed").toInt();

        // 关键词过滤
        if (!nameFilter.isEmpty() && !name.contains(nameFilter, Qt::CaseInsensitive)) continue;

        // 分类过滤
        if (catFilter != "全部分类" && category != catFilter) continue;

        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::UserRole, i);

        // 文本显示格式：[分类] 任务名称
        QString displayText = QString("[%1] %2").arg(category).arg(name);

        // 视觉逻辑：已完成显示灰色斜体，未完成按优先级着色
        if (isDone) {
            item->setText("[已完成] " + displayText);
            item->setForeground(Qt::gray);
            QFont font = item->font();
            font.setItalic(true);
            item->setFont(font);
        } else {
            item->setText(displayText);
            if (prio == 0) item->setForeground(QColor("#e74c3c"));      // 高：红
            else if (prio == 1) item->setForeground(QColor("#f39c12")); // 中：橙
            else item->setForeground(QColor("#27ae60"));                // 低：绿
        }
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->editPanel->setEnabled(true); // 激活编辑面板
    int row = item->data(Qt::UserRole).toInt();
    QSqlRecord rec = model->record(row);

    ui->editName->setText(rec.value("name").toString());
    ui->editDesc->setPlainText(rec.value("description").toString());
    ui->editDeadline->setDateTime(QDateTime::fromString(rec.value("deadline").toString(),
                                                        "yyyy-MM-dd HH:mm"));
    ui->editPriority->setCurrentIndex(rec.value("priority").toInt());
    ui->checkCompleted->setChecked(rec.value("is_completed").toInt() == 1);

    // 设置分类下拉框的值
    ui->editCategory->setCurrentText(rec.value("category").toString());
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
    // 保存分类 (数据库第 8 列，索引为 7)
    model->setData(model->index(row, 7), ui->editCategory->currentText());

    if (model->submitAll()) {
        QMessageBox::information(this, "成功", "任务已更新");
        updateListView();
    } else {
        QMessageBox::warning(this, "错误", "保存失败: " + model->lastError().text());
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
    rec.setValue("category", "默认");

    if (model->insertRecord(-1, rec)) {
        model->submitAll();
        updateListView();
    }
}

void MainWindow::on_deleteTaskBtn_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (!item) return;

    if (QMessageBox::question(this, "确认", "确定删除该任务？") == QMessageBox::Yes) {
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
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("导出报表");
    msgBox.setText("请选择导出格式：");
    QPushButton *excelBtn = msgBox.addButton("Excel", QMessageBox::ActionRole);
    QPushButton *pdfBtn = msgBox.addButton("PDF", QMessageBox::ActionRole);
    msgBox.addButton("取消", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == excelBtn) {
        exportToExcel(model); // 调用 Excel 导出
    } else if (msgBox.clickedButton() == pdfBtn) {
        exportToPdf(model);   // 调用 PDF 导出
    }
}
void MainWindow::handleReminder(const QString &name, const QString &time)
{
    // 将两个参数放在同一个 .arg() 调用中
    QMessageBox::information(this, "任务提醒",
                             QString("任务: %1\n截止日期已到: %2").arg(name, time));
    updateListView();
}

MainWindow::~MainWindow()
{
    // 安全停止提醒线程
    if (reminderThread->isRunning()) {
        reminderThread->quit();
        reminderThread->wait();
    }
    delete ui;
}
