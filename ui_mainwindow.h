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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *searchLineEdit;
    QComboBox *sortComboBox;
    QListWidget *listWidget;
    QPushButton *addTaskBtn;
    QFrame *editPanel;
    QFormLayout *formLayout;
    QPushButton *saveEditBtn;
    QPushButton *deleteTaskBtn;
    QLabel *label;
    QLineEdit *editName;
    QLabel *label_3;
    QLabel *label_2;
    QTextEdit *editDesc;
    QDateTimeEdit *editDeadline;
    QComboBox *editPriority;
    QLabel *label_4;
    QCheckBox *checkCompleted;
    QLabel *label_5;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* \347\252\227\345\217\243\350\203\214\346\231\257 */\n"
"QMainWindow { background-color: #f5f6fa; }\n"
"\n"
"/* \345\217\263\344\276\247 Frame \347\276\216\345\214\226 */\n"
"QFrame#editPanel {\n"
"    background-color: white;\n"
"    border: 1px solid #dcdde1;\n"
"    border-radius: 10px;\n"
"    margin: 5px;\n"
"}\n"
"\n"
"/* \346\220\234\347\264\242\346\241\206\345\234\206\350\247\222 */\n"
"QLineEdit#searchLineEdit {\n"
"    padding: 6px;\n"
"    border-radius: 15px;\n"
"    border: 1px solid #dcdde1;\n"
"}\n"
"\n"
"/* \346\214\211\351\222\256\346\240\267\345\274\217 */\n"
"QPushButton {\n"
"    background-color: #4a90e2;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#deleteTaskBtn {\n"
"    background-color: #e74c3c; /* \345\210\240\351\231\244\346\214\211\351\222\256\347\272\242\350\211\262 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #357abd;\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: #ec"
                        "f0f1; /* \346\265\205\347\201\260\350\211\262\351\200\211\344\270\255\350\203\214\346\231\257 */\n"
"    color: inherit;            /* \344\277\235\346\214\201\346\210\221\344\273\254\351\200\232\350\277\207\344\273\243\347\240\201\350\256\276\347\275\256\347\232\204\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    border-left: 5px solid #3498db; \n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        searchLineEdit = new QLineEdit(widget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        verticalLayout_2->addWidget(searchLineEdit);

        sortComboBox = new QComboBox(widget);
        sortComboBox->setObjectName(QString::fromUtf8("sortComboBox"));

        verticalLayout_2->addWidget(sortComboBox);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        addTaskBtn = new QPushButton(widget);
        addTaskBtn->setObjectName(QString::fromUtf8("addTaskBtn"));

        verticalLayout_2->addWidget(addTaskBtn);


        horizontalLayout->addWidget(widget);

        editPanel = new QFrame(centralwidget);
        editPanel->setObjectName(QString::fromUtf8("editPanel"));
        editPanel->setFrameShape(QFrame::StyledPanel);
        editPanel->setFrameShadow(QFrame::Sunken);
        formLayout = new QFormLayout(editPanel);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        saveEditBtn = new QPushButton(editPanel);
        saveEditBtn->setObjectName(QString::fromUtf8("saveEditBtn"));

        formLayout->setWidget(7, QFormLayout::FieldRole, saveEditBtn);

        deleteTaskBtn = new QPushButton(editPanel);
        deleteTaskBtn->setObjectName(QString::fromUtf8("deleteTaskBtn"));

        formLayout->setWidget(7, QFormLayout::LabelRole, deleteTaskBtn);

        label = new QLabel(editPanel);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        editName = new QLineEdit(editPanel);
        editName->setObjectName(QString::fromUtf8("editName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, editName);

        label_3 = new QLabel(editPanel);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_2 = new QLabel(editPanel);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        editDesc = new QTextEdit(editPanel);
        editDesc->setObjectName(QString::fromUtf8("editDesc"));

        formLayout->setWidget(1, QFormLayout::FieldRole, editDesc);

        editDeadline = new QDateTimeEdit(editPanel);
        editDeadline->setObjectName(QString::fromUtf8("editDeadline"));

        formLayout->setWidget(2, QFormLayout::FieldRole, editDeadline);

        editPriority = new QComboBox(editPanel);
        editPriority->setObjectName(QString::fromUtf8("editPriority"));

        formLayout->setWidget(5, QFormLayout::FieldRole, editPriority);

        label_4 = new QLabel(editPanel);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        checkCompleted = new QCheckBox(editPanel);
        checkCompleted->setObjectName(QString::fromUtf8("checkCompleted"));

        formLayout->setWidget(3, QFormLayout::FieldRole, checkCompleted);

        label_5 = new QLabel(editPanel);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);


        horizontalLayout->addWidget(editPanel);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        addTaskBtn->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\273\273\345\212\241", nullptr));
        saveEditBtn->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\277\256\346\224\271", nullptr));
        deleteTaskBtn->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\273\273\345\212\241", nullptr));
        label->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\220\215\347\247\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\217\217\350\277\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\210\252\346\255\242\346\227\266\351\227\264", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\344\274\230\345\205\210\347\272\247", nullptr));
        checkCompleted->setText(QApplication::translate("MainWindow", "\345\267\262\345\256\214\346\210\220", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\345\256\214\346\210\220\346\203\205\345\206\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
