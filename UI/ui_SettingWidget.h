/********************************************************************************
** Form generated from reading UI file 'SettingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "SettingLabel.h"

QT_BEGIN_NAMESPACE

class Ui_SettingWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *setting;
    SettingLabel *decode;
    SettingLabel *d3d11vaFilter;
    SettingLabel *about;
    SettingLabel *coder;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *centerLayout;

    void setupUi(QWidget *SettingWidget)
    {
        if (SettingWidget->objectName().isEmpty())
            SettingWidget->setObjectName(QString::fromUtf8("SettingWidget"));
        SettingWidget->resize(797, 642);
        SettingWidget->setFocusPolicy(Qt::NoFocus);
        SettingWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(SettingWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        setting = new QLabel(SettingWidget);
        setting->setObjectName(QString::fromUtf8("setting"));
        setting->setMinimumSize(QSize(0, 60));
        setting->setMaximumSize(QSize(1000, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        setting->setFont(font);
        setting->setStyleSheet(QString::fromUtf8("color: rgb(240, 240, 240);"));
        setting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(setting);

        decode = new SettingLabel(SettingWidget);
        decode->setObjectName(QString::fromUtf8("decode"));
        decode->setMinimumSize(QSize(0, 45));
        decode->setMaximumSize(QSize(1000, 45));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        decode->setFont(font1);
        decode->setCursor(QCursor(Qt::PointingHandCursor));
        decode->setFocusPolicy(Qt::NoFocus);
        decode->setStyleSheet(QString::fromUtf8(""));
        decode->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(decode);

        d3d11vaFilter = new SettingLabel(SettingWidget);
        d3d11vaFilter->setObjectName(QString::fromUtf8("d3d11vaFilter"));
        d3d11vaFilter->setMinimumSize(QSize(0, 45));
        d3d11vaFilter->setMaximumSize(QSize(1000, 45));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        d3d11vaFilter->setFont(font2);
        d3d11vaFilter->setCursor(QCursor(Qt::PointingHandCursor));
        d3d11vaFilter->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(d3d11vaFilter);

        about = new SettingLabel(SettingWidget);
        about->setObjectName(QString::fromUtf8("about"));
        about->setMinimumSize(QSize(0, 45));
        about->setMaximumSize(QSize(1000, 45));
        about->setFont(font1);
        about->setCursor(QCursor(Qt::PointingHandCursor));
        about->setFocusPolicy(Qt::NoFocus);
        about->setStyleSheet(QString::fromUtf8(""));
        about->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(about);

        coder = new SettingLabel(SettingWidget);
        coder->setObjectName(QString::fromUtf8("coder"));
        coder->setMinimumSize(QSize(0, 45));
        coder->setMaximumSize(QSize(1000, 45));
        coder->setFont(font2);
        coder->setCursor(QCursor(Qt::PointingHandCursor));
        coder->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(coder);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        centerLayout = new QVBoxLayout();
        centerLayout->setSpacing(0);
        centerLayout->setObjectName(QString::fromUtf8("centerLayout"));
        centerLayout->setContentsMargins(-1, 60, -1, -1);

        horizontalLayout->addLayout(centerLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 6);

        retranslateUi(SettingWidget);

        QMetaObject::connectSlotsByName(SettingWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingWidget)
    {
        SettingWidget->setWindowTitle(QString());
        setting->setText(QCoreApplication::translate("SettingWidget", "    \350\256\276\347\275\256", nullptr));
        decode->setText(QCoreApplication::translate("SettingWidget", "\350\247\243\347\240\201", nullptr));
        d3d11vaFilter->setText(QCoreApplication::translate("SettingWidget", "D3D11VA\346\273\244\351\225\234", nullptr));
        about->setText(QCoreApplication::translate("SettingWidget", "\345\205\263\344\272\216", nullptr));
        coder->setText(QCoreApplication::translate("SettingWidget", "\350\201\224\347\263\273\344\275\234\350\200\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWidget: public Ui_SettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
