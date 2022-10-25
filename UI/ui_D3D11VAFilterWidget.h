/********************************************************************************
** Form generated from reading UI file 'D3D11VAFilterWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_D3D11VAFILTERWIDGET_H
#define UI_D3D11VAFILTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_D3D11VAFilterWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSlider *brightness;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSlider *contrast;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QSlider *hue;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_4;
    QSlider *saturation;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_5;
    QSlider *edge_enhancement;
    QSpacerItem *verticalSpacer_6;
    QPushButton *reset;

    void setupUi(QWidget *D3D11VAFilterWidget)
    {
        if (D3D11VAFilterWidget->objectName().isEmpty())
            D3D11VAFilterWidget->setObjectName(QString::fromUtf8("D3D11VAFilterWidget"));
        D3D11VAFilterWidget->resize(692, 634);
        verticalLayout_2 = new QVBoxLayout(D3D11VAFilterWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(D3D11VAFilterWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 0, -1, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        brightness = new QSlider(widget);
        brightness->setObjectName(QString::fromUtf8("brightness"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(brightness->sizePolicy().hasHeightForWidth());
        brightness->setSizePolicy(sizePolicy1);
        brightness->setCursor(QCursor(Qt::PointingHandCursor));
        brightness->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 4px; \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"	background:rgb(150,150,150);\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"	background:rgb(40,40,40);\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: white;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 20px;\n"
"	height: 20px;\n"
"    border-radius: 10px;\n"
"	top: -8px;\n"
"	bottom: -8px;\n"
"}"));
        brightness->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(brightness);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        verticalLayout_3->addWidget(label_2);

        contrast = new QSlider(widget);
        contrast->setObjectName(QString::fromUtf8("contrast"));
        contrast->setCursor(QCursor(Qt::PointingHandCursor));
        contrast->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 4px; \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"	background:rgb(150,150,150);\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"	background:rgb(40,40,40);\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: white;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 20px;\n"
"	height: 20px;\n"
"    border-radius: 10px;\n"
"	top: -8px;\n"
"	bottom: -8px;\n"
"}"));
        contrast->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(contrast);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        hue = new QSlider(widget);
        hue->setObjectName(QString::fromUtf8("hue"));
        hue->setCursor(QCursor(Qt::PointingHandCursor));
        hue->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 4px; \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"	background:rgb(150,150,150);\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"	background:rgb(40,40,40);\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: white;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 20px;\n"
"	height: 20px;\n"
"    border-radius: 10px;\n"
"	top: -8px;\n"
"	bottom: -8px;\n"
"}"));
        hue->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(hue);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);

        verticalLayout_3->addWidget(label_4);

        saturation = new QSlider(widget);
        saturation->setObjectName(QString::fromUtf8("saturation"));
        saturation->setCursor(QCursor(Qt::PointingHandCursor));
        saturation->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 4px; \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"	background:rgb(150,150,150);\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"	background:rgb(40,40,40);\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: white;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 20px;\n"
"	height: 20px;\n"
"    border-radius: 10px;\n"
"	top: -8px;\n"
"	bottom: -8px;\n"
"}"));
        saturation->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(saturation);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);

        verticalLayout_3->addWidget(label_5);

        edge_enhancement = new QSlider(widget);
        edge_enhancement->setObjectName(QString::fromUtf8("edge_enhancement"));
        edge_enhancement->setCursor(QCursor(Qt::PointingHandCursor));
        edge_enhancement->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 4px; \n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"	background:rgb(150,150,150);\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"	background:rgb(40,40,40);\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: white;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 20px;\n"
"	height: 20px;\n"
"    border-radius: 10px;\n"
"	top: -8px;\n"
"	bottom: -8px;\n"
"}"));
        edge_enhancement->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(edge_enhancement);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_6);

        reset = new QPushButton(widget);
        reset->setObjectName(QString::fromUtf8("reset"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(reset->sizePolicy().hasHeightForWidth());
        reset->setSizePolicy(sizePolicy2);
        reset->setMinimumSize(QSize(70, 35));
        reset->setMaximumSize(QSize(70, 35));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        reset->setFont(font1);
        reset->setCursor(QCursor(Qt::PointingHandCursor));
        reset->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_3->addWidget(reset);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addWidget(widget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(D3D11VAFilterWidget);

        QMetaObject::connectSlotsByName(D3D11VAFilterWidget);
    } // setupUi

    void retranslateUi(QWidget *D3D11VAFilterWidget)
    {
        D3D11VAFilterWidget->setWindowTitle(QCoreApplication::translate("D3D11VAFilterWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\344\272\256\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\345\257\271\346\257\224\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\350\211\262\350\260\203", nullptr));
        label_4->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\351\245\261\345\222\214\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\350\276\271\347\274\230\345\242\236\345\274\272", nullptr));
        reset->setText(QCoreApplication::translate("D3D11VAFilterWidget", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class D3D11VAFilterWidget: public Ui_D3D11VAFilterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D3D11VAFILTERWIDGET_H
