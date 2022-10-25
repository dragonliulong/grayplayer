/********************************************************************************
** Form generated from reading UI file 'DecodeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECODEWIDGET_H
#define UI_DECODEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DecodeWidget
{
public:
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QComboBox *decodeMode;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *bottomLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *explain;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *save;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *DecodeWidget)
    {
        if (DecodeWidget->objectName().isEmpty())
            DecodeWidget->setObjectName(QString::fromUtf8("DecodeWidget"));
        DecodeWidget->resize(834, 802);
        verticalLayout_5 = new QVBoxLayout(DecodeWidget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_4 = new QLabel(DecodeWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_4);

        verticalSpacer_6 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        decodeMode = new QComboBox(DecodeWidget);
        decodeMode->addItem(QString());
        decodeMode->addItem(QString());
        decodeMode->addItem(QString());
        decodeMode->setObjectName(QString::fromUtf8("decodeMode"));
        sizePolicy.setHeightForWidth(decodeMode->sizePolicy().hasHeightForWidth());
        decodeMode->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Palatino Linotype"));
        font1.setBold(false);
        font1.setWeight(50);
        decodeMode->setFont(font1);
        decodeMode->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	background:rgb(240,240,240);\n"
"    border: 1px solid gray;\n"
"    padding: 1px 2px 1px 2px;  \n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
" \n"
"    border-width: 1px;\n"
"    border-color: darkgray;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/down_arrow.jpg);\n"
"}"));
        decodeMode->setMaxVisibleItems(100);
        decodeMode->setMaxCount(100);
        decodeMode->setFrame(true);

        horizontalLayout_3->addWidget(decodeMode);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 10);

        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        bottomLayout = new QVBoxLayout();
        bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));

        verticalLayout_5->addLayout(bottomLayout);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        explain = new QPushButton(DecodeWidget);
        explain->setObjectName(QString::fromUtf8("explain"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(explain->sizePolicy().hasHeightForWidth());
        explain->setSizePolicy(sizePolicy1);
        explain->setMinimumSize(QSize(70, 35));
        explain->setMaximumSize(QSize(70, 35));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        explain->setFont(font2);
        explain->setCursor(QCursor(Qt::PointingHandCursor));
        explain->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"	color: rgb(0,0,0);\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: navy; /* make the default button prominent */\n"
"}"));

        horizontalLayout_4->addWidget(explain);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        save = new QPushButton(DecodeWidget);
        save->setObjectName(QString::fromUtf8("save"));
        sizePolicy1.setHeightForWidth(save->sizePolicy().hasHeightForWidth());
        save->setSizePolicy(sizePolicy1);
        save->setMinimumSize(QSize(70, 35));
        save->setMaximumSize(QSize(70, 35));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setWeight(50);
        save->setFont(font3);
        save->setCursor(QCursor(Qt::PointingHandCursor));
        save->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"	color: rgb(0,0,0);\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: navy; /* make the default button prominent */\n"
"}"));
        save->setFlat(false);

        horizontalLayout_4->addWidget(save);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_3);

        verticalLayout_5->setStretch(4, 10);
        verticalLayout_5->setStretch(6, 1);

        retranslateUi(DecodeWidget);

        decodeMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DecodeWidget);
    } // setupUi

    void retranslateUi(QWidget *DecodeWidget)
    {
        DecodeWidget->setWindowTitle(QCoreApplication::translate("DecodeWidget", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("DecodeWidget", "\350\247\243\347\240\201\346\226\271\345\274\217", nullptr));
        decodeMode->setItemText(0, QCoreApplication::translate("DecodeWidget", "\350\275\257\350\247\243", nullptr));
        decodeMode->setItemText(1, QCoreApplication::translate("DecodeWidget", "DXVA2\347\241\254\350\247\243", nullptr));
        decodeMode->setItemText(2, QCoreApplication::translate("DecodeWidget", "D3D11VA\347\241\254\350\247\243", nullptr));

        explain->setText(QCoreApplication::translate("DecodeWidget", "\350\257\264\346\230\216", nullptr));
        save->setText(QCoreApplication::translate("DecodeWidget", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DecodeWidget: public Ui_DecodeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECODEWIDGET_H
