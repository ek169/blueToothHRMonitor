/********************************************************************************
** Form generated from reading UI file 'DeviceSearcher.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICESEARCHER_H
#define UI_DEVICESEARCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DeviceSearcher
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPushButton *scan;
    QPushButton *clear;
    QPushButton *quit;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListWidget *list;

    void setupUi(QDialog *DeviceSearcher)
    {
        if (DeviceSearcher->objectName().isEmpty())
            DeviceSearcher->setObjectName(QString::fromUtf8("DeviceSearcher"));
        DeviceSearcher->resize(644, 345);
        horizontalLayout = new QHBoxLayout(DeviceSearcher);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(DeviceSearcher);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::MarkdownText);

        verticalLayout_2->addWidget(label);

        scan = new QPushButton(DeviceSearcher);
        scan->setObjectName(QString::fromUtf8("scan"));

        verticalLayout_2->addWidget(scan);

        clear = new QPushButton(DeviceSearcher);
        clear->setObjectName(QString::fromUtf8("clear"));

        verticalLayout_2->addWidget(clear);

        quit = new QPushButton(DeviceSearcher);
        quit->setObjectName(QString::fromUtf8("quit"));

        verticalLayout_2->addWidget(quit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(DeviceSearcher);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        list = new QListWidget(DeviceSearcher);
        list->setObjectName(QString::fromUtf8("list"));

        verticalLayout->addWidget(list);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(DeviceSearcher);
        QObject::connect(quit, SIGNAL(clicked()), DeviceSearcher, SLOT(accept()));
        QObject::connect(clear, SIGNAL(clicked()), list, SLOT(clear()));

        QMetaObject::connectSlotsByName(DeviceSearcher);
    } // setupUi

    void retranslateUi(QDialog *DeviceSearcher)
    {
        DeviceSearcher->setWindowTitle(QCoreApplication::translate("DeviceSearcher", "Bluetooth Scanner", nullptr));
        label->setText(QCoreApplication::translate("DeviceSearcher", "<html><head/><body><p><span style=\" font-weight:600;\">HR Monitor Finder</span></p><p><br/></p></body></html>", nullptr));
        scan->setText(QCoreApplication::translate("DeviceSearcher", "Search", nullptr));
        clear->setText(QCoreApplication::translate("DeviceSearcher", "Reset", nullptr));
        quit->setText(QCoreApplication::translate("DeviceSearcher", "Exit", nullptr));
        label_2->setText(QCoreApplication::translate("DeviceSearcher", "<em>Available Devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceSearcher: public Ui_DeviceSearcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICESEARCHER_H
