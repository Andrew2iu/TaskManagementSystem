/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLineEdit;
    QPushButton *addTaskBtn;
    QPushButton *exportBtn;
    QPushButton *deleteTaskBtn;
    QTableView *tableView;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* \344\270\273\347\252\227\345\217\243\350\203\214\346\231\257 */\n"
"QMainWindow {\n"
"    background-color: #f5f6fa;\n"
"}\n"
"\n"
"/* \346\214\211\351\222\256\347\276\216\345\214\226 */\n"
"QPushButton {\n"
"    background-color: #4a90e2;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #357abd;\n"
"}\n"
"QPushButton#deleteTaskBtn {\n"
"    background-color: #e74c3c; /* \345\210\240\351\231\244\346\214\211\351\222\256\344\275\277\347\224\250\347\272\242\350\211\262 */\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\357\274\210\346\220\234\347\264\242\346\241\206\357\274\211 */\n"
"QLineEdit {\n"
"    border: 1px solid #dcdde1;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    background: white;\n"
"}\n"
"\n"
"/* \350\241\250\346\240\274\347\276\216\345\214\226 */\n"
"QTableView {\n"
"    background-color: white;\n"
"    border: 1px solid #dcdde1;\n"
"    gridline-color: #f1f2f6;\n"
""
                        "    selection-background-color: #4a90e2;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #f8f9fa;\n"
"    padding: 4px;\n"
"    border: 1px solid #dcdde1;\n"
"    font-weight: bold;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayout->addWidget(searchLineEdit);

        addTaskBtn = new QPushButton(centralwidget);
        addTaskBtn->setObjectName(QString::fromUtf8("addTaskBtn"));

        horizontalLayout->addWidget(addTaskBtn);

        exportBtn = new QPushButton(centralwidget);
        exportBtn->setObjectName(QString::fromUtf8("exportBtn"));

        horizontalLayout->addWidget(exportBtn);

        deleteTaskBtn = new QPushButton(centralwidget);
        deleteTaskBtn->setObjectName(QString::fromUtf8("deleteTaskBtn"));

        horizontalLayout->addWidget(deleteTaskBtn);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableView);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        searchLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\360\237\224\215 \350\276\223\345\205\245\344\273\273\345\212\241\345\220\215\347\247\260\346\220\234\347\264\242...", nullptr));
        addTaskBtn->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        exportBtn->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\344\273\273\345\212\241", nullptr));
        deleteTaskBtn->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\273\273\345\212\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
