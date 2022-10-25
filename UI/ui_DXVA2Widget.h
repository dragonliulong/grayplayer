/********************************************************************************
** Form generated from reading UI file 'DXVA2Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DXVA2WIDGET_H
#define UI_DXVA2WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DXVA2Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *doubleSwapChain;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *DXVA2Widget)
    {
        if (DXVA2Widget->objectName().isEmpty())
            DXVA2Widget->setObjectName(QString::fromUtf8("DXVA2Widget"));
        DXVA2Widget->resize(686, 627);
        verticalLayout = new QVBoxLayout(DXVA2Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        doubleSwapChain = new QCheckBox(DXVA2Widget);
        doubleSwapChain->setObjectName(QString::fromUtf8("doubleSwapChain"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setBold(true);
        font.setWeight(75);
        doubleSwapChain->setFont(font);

        horizontalLayout->addWidget(doubleSwapChain);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(DXVA2Widget);

        QMetaObject::connectSlotsByName(DXVA2Widget);
    } // setupUi

    void retranslateUi(QWidget *DXVA2Widget)
    {
        DXVA2Widget->setWindowTitle(QCoreApplication::translate("DXVA2Widget", "Form", nullptr));
        doubleSwapChain->setText(QCoreApplication::translate("DXVA2Widget", " \345\217\214\344\272\244\346\215\242\351\223\276\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DXVA2Widget: public Ui_DXVA2Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DXVA2WIDGET_H
