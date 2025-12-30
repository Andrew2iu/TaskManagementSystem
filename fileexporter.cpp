#include "fileexporter.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QVariant>
#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>

// 导出为 Excel 1
void exportToExcel(QAbstractItemModel *model)
{
    if (!model) return;
    QString path = QFileDialog::getSaveFileName(nullptr, "导出 Excel", "tasks.xls",
                                                "Excel Files (*.xls)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setGenerateByteOrderMark(true); // 解决 Excel 中文乱码
        out << "任务名称\t截止时间\t状态\n";
        for (int i = 0; i < model->rowCount(); ++i) {
            bool isDone = model->index(i, 5).data().toInt() == 1;
            out << model->index(i, 1).data().toString() << "\t"
                << model->index(i, 3).data().toString() << "\t"
                << (isDone ? "已完成" : "待处理") << "\n";
        }
        file.close();
        QMessageBox::information(nullptr, "提示", "Excel 导出成功！");
    }
}

// 导出为 PDF
void exportToPdf(QAbstractItemModel *model)
{
    if (!model) return;
    QString path = QFileDialog::getSaveFileName(nullptr, "导出 PDF", "tasks.pdf",
                                                "PDF Files (*.pdf)");
    if (path.isEmpty()) return;

    QPdfWriter pdfWriter(path);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setPen(Qt::black);
    painter.setFont(QFont("SimSun", 16, QFont::Bold));
    painter.drawText(pdfWriter.width() / 3, 1000, "任务统计报表");

    painter.setFont(QFont("SimSun", 10));
    int y = 2000;
    painter.drawText(0, y, "任务名称");
    painter.drawText(4000, y, "截止时间");
    painter.drawText(8000, y, "状态");

    y += 500;
    painter.drawLine(0, y, pdfWriter.width(), y);
    y += 400;

    for (int i = 0; i < model->rowCount(); ++i) {
        painter.drawText(0, y, model->index(i, 1).data().toString());
        painter.drawText(4000, y, model->index(i, 3).data().toString());
        bool isDone = model->index(i, 5).data().toInt() == 1;
        painter.drawText(8000, y, isDone ? "已完成" : "待处理");
        y += 400;
        if (y > pdfWriter.height() - 500) {
            pdfWriter.newPage();
            y = 1000;
        }
    }
    painter.end();
    QMessageBox::information(nullptr, "提示", "PDF 导出成功！");
}
