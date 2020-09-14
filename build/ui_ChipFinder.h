/********************************************************************************
** Form generated from reading UI file 'ChipFinder.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHIPFINDER_H
#define UI_CHIPFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChipFinder
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *list;
    QHBoxLayout *horizontalLayout;
    QPushButton *close;

    void setupUi(QDialog *ChipFinder)
    {
        if (ChipFinder->objectName().isEmpty())
            ChipFinder->setObjectName(QString::fromUtf8("ChipFinder"));
        ChipFinder->resize(173, 339);
        verticalLayout = new QVBoxLayout(ChipFinder);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ChipFinder);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::MarkdownText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        list = new QListWidget(ChipFinder);
        list->setObjectName(QString::fromUtf8("list"));

        verticalLayout->addWidget(list);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        close = new QPushButton(ChipFinder);
        close->setObjectName(QString::fromUtf8("close"));

        horizontalLayout->addWidget(close);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(list, close);

        retranslateUi(ChipFinder);
        QObject::connect(close, SIGNAL(clicked()), ChipFinder, SLOT(accept()));

        QMetaObject::connectSlotsByName(ChipFinder);
    } // setupUi

    void retranslateUi(QDialog *ChipFinder)
    {
        ChipFinder->setWindowTitle(QCoreApplication::translate("ChipFinder", "Available Services", nullptr));
        label->setText(QCoreApplication::translate("ChipFinder", "<html><head/><body><p><span style=\" font-style:italic;\">Available Chips</span></p></body></html>", nullptr));
        close->setText(QCoreApplication::translate("ChipFinder", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChipFinder: public Ui_ChipFinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHIPFINDER_H
