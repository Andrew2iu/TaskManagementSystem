#ifndef FILEEXPORTER_H
#define FILEEXPORTER_H
#include <QAbstractItemModel>

void exportToExcel(QAbstractItemModel *model);
void exportToPdf(QAbstractItemModel *model)// 新增 PDF 导出接口
#endif
