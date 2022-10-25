/********************************************************************************
** Form generated from reading UI file 'SWWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWWIDGET_H
#define UI_SWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SWWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *swThreadCount;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SWWidget)
    {
        if (SWWidget->objectName().isEmpty())
            SWWidget->setObjectName(QString::fromUtf8("SWWidget"));
        SWWidget->resize(689, 638);
        verticalLayout = new QVBoxLayout(SWWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(SWWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_5);

        verticalSpacer_2 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        swThreadCount = new QSpinBox(SWWidget);
        swThreadCount->setObjectName(QString::fromUtf8("swThreadCount"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(swThreadCount->sizePolicy().hasHeightForWidth());
        swThreadCount->setSizePolicy(sizePolicy1);
        swThreadCount->setMinimumSize(QSize(50, 20));
        swThreadCount->setMaximumSize(QSize(50, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Cambria Math"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        swThreadCount->setFont(font1);
        swThreadCount->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        swThreadCount->setAlignment(Qt::AlignCenter);
        swThreadCount->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        swThreadCount->setMinimum(1);
        swThreadCount->setMaximum(32);

        horizontalLayout_4->addWidget(swThreadCount);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 586, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SWWidget);

        QMetaObject::connectSlotsByName(SWWidget);
    } // setupUi

    void retranslateUi(QWidget *SWWidget)
    {
        SWWidget->setWindowTitle(QCoreApplication::translate("SWWidget", "Form", nullptr));
        label_5->setText(QCoreApplication::translate("SWWidget", "\347\272\277\347\250\213\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SWWidget: public Ui_SWWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWWIDGET_H
