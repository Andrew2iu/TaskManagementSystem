#include "fileexporter.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QVariant>

void exportToExcel(QAbstractItemModel *model)
{
    if (!model) return;
    QString path = QFileDialog::getSaveFileName(nullptr, "导出报表", "tasks.xls",
                                                "Excel Files (*.xls)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << "任务名称\t截止时间\t状态\n";
        for (int i = 0; i < model->rowCount(); ++i) {
            out << model->index(i, 1).data().toString() << "\t"
                << model->index(i, 3).data().toString() << "\t"
                << model->index(i, 5).data().toString() << "\n";
        }
        file.close();
        QMessageBox::information(nullptr, "提示", "导出成功！");
    }
}
