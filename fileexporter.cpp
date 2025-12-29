#include "fileexporter.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

void exportToExcel(QAbstractItemModel *model)
{
    if (!model || model->rowCount() == 0) return;

    QString path = QFileDialog::getSaveFileName(nullptr, "导出报表", "tasks.csv",
                                                "CSV Files (*.csv)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setGenerateByteOrderMark(true); // 解决 Excel 中文乱码
        out << "任务名称,截止时间,状态\n";

        for (int i = 0; i < model->rowCount(); ++i) {
            QString name = model->index(i, 1).data().toString();
            QString time = model->index(i, 3).data().toString();
            int status = model->index(i, 5).data().toInt();
            out << name << "," << time << "," << (status == 1 ? "已完成" : "进行中") << "\n";
        }
        file.close();
        QMessageBox::information(nullptr, "提示", "导出成功！");
    }
}
