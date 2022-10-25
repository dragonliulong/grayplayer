/********************************************************************************
** Form generated from reading UI file 'D3D11VAWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_D3D11VAWIDGET_H
#define UI_D3D11VAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_D3D11VAWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *d3d11vaAdapter;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *d3d11Fomat;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QSpinBox *d3d11SwapChainCount;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_11;
    QComboBox *d3d11SwapEffect;
    QSpacerItem *horizontalSpacer_12;

    void setupUi(QWidget *D3D11VAWidget)
    {
        if (D3D11VAWidget->objectName().isEmpty())
            D3D11VAWidget->setObjectName(QString::fromUtf8("D3D11VAWidget"));
        D3D11VAWidget->resize(852, 730);
        verticalLayout = new QVBoxLayout(D3D11VAWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(D3D11VAWidget);
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

        verticalLayout->addWidget(label_4);

        verticalSpacer_8 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        d3d11vaAdapter = new QComboBox(D3D11VAWidget);
        d3d11vaAdapter->addItem(QString());
        d3d11vaAdapter->setObjectName(QString::fromUtf8("d3d11vaAdapter"));
        sizePolicy.setHeightForWidth(d3d11vaAdapter->sizePolicy().hasHeightForWidth());
        d3d11vaAdapter->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Palatino Linotype"));
        d3d11vaAdapter->setFont(font1);
        d3d11vaAdapter->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        horizontalLayout_5->addWidget(d3d11vaAdapter);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 11);

        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label = new QLabel(D3D11VAWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_9 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        d3d11Fomat = new QComboBox(D3D11VAWidget);
        d3d11Fomat->addItem(QString());
        d3d11Fomat->addItem(QString());
        d3d11Fomat->addItem(QString());
        d3d11Fomat->addItem(QString());
        d3d11Fomat->addItem(QString());
        d3d11Fomat->setObjectName(QString::fromUtf8("d3d11Fomat"));
        sizePolicy.setHeightForWidth(d3d11Fomat->sizePolicy().hasHeightForWidth());
        d3d11Fomat->setSizePolicy(sizePolicy);
        d3d11Fomat->setFont(font1);
        d3d11Fomat->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        horizontalLayout_6->addWidget(d3d11Fomat);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 1);
        horizontalLayout_6->setStretch(2, 11);

        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        label_2 = new QLabel(D3D11VAWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_2);

        verticalSpacer_10 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        d3d11SwapChainCount = new QSpinBox(D3D11VAWidget);
        d3d11SwapChainCount->setObjectName(QString::fromUtf8("d3d11SwapChainCount"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(d3d11SwapChainCount->sizePolicy().hasHeightForWidth());
        d3d11SwapChainCount->setSizePolicy(sizePolicy1);
        d3d11SwapChainCount->setMinimumSize(QSize(50, 20));
        d3d11SwapChainCount->setMaximumSize(QSize(50, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Cambria Math"));
        d3d11SwapChainCount->setFont(font2);
        d3d11SwapChainCount->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);\n"
""));
        d3d11SwapChainCount->setAlignment(Qt::AlignCenter);
        d3d11SwapChainCount->setMinimum(1);
        d3d11SwapChainCount->setMaximum(8);

        horizontalLayout_7->addWidget(d3d11SwapChainCount);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);
        horizontalLayout_7->setStretch(2, 11);

        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        label_3 = new QLabel(D3D11VAWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_3);

        verticalSpacer_11 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_11);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);

        d3d11SwapEffect = new QComboBox(D3D11VAWidget);
        d3d11SwapEffect->addItem(QString());
        d3d11SwapEffect->addItem(QString());
        d3d11SwapEffect->addItem(QString());
        d3d11SwapEffect->addItem(QString());
        d3d11SwapEffect->setObjectName(QString::fromUtf8("d3d11SwapEffect"));
        sizePolicy.setHeightForWidth(d3d11SwapEffect->sizePolicy().hasHeightForWidth());
        d3d11SwapEffect->setSizePolicy(sizePolicy);
        d3d11SwapEffect->setFont(font1);
        d3d11SwapEffect->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        horizontalLayout_8->addWidget(d3d11SwapEffect);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 1);
        horizontalLayout_8->setStretch(2, 11);

        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(D3D11VAWidget);

        QMetaObject::connectSlotsByName(D3D11VAWidget);
    } // setupUi

    void retranslateUi(QWidget *D3D11VAWidget)
    {
        D3D11VAWidget->setWindowTitle(QCoreApplication::translate("D3D11VAWidget", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("D3D11VAWidget", "\350\247\243\347\240\201\346\230\276\345\215\241", nullptr));
        d3d11vaAdapter->setItemText(0, QCoreApplication::translate("D3D11VAWidget", "\351\273\230\350\256\244", nullptr));

        label->setText(QCoreApplication::translate("D3D11VAWidget", "\346\230\276\347\244\272\346\240\274\345\274\217", nullptr));
        d3d11Fomat->setItemText(0, QCoreApplication::translate("D3D11VAWidget", "DXGI_FORMAT_B8G8R8A8_UNORM", nullptr));
        d3d11Fomat->setItemText(1, QCoreApplication::translate("D3D11VAWidget", "DXGI_FORMAT_R8G8B8A8_UNORM", nullptr));
        d3d11Fomat->setItemText(2, QCoreApplication::translate("D3D11VAWidget", "DXGI_FORMAT_B8G8R8A8_UNORM_SRGB", nullptr));
        d3d11Fomat->setItemText(3, QCoreApplication::translate("D3D11VAWidget", "DXGI_FORMAT_R8G8B8A8_UNORM_SRGB", nullptr));
        d3d11Fomat->setItemText(4, QCoreApplication::translate("D3D11VAWidget", "DXGI_FORMAT_R10G10B10A2_UNORM", nullptr));

        label_2->setText(QCoreApplication::translate("D3D11VAWidget", "\344\272\244\346\215\242\351\223\276\344\270\252\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("D3D11VAWidget", "\344\272\244\346\215\242\346\225\210\346\236\234", nullptr));
        d3d11SwapEffect->setItemText(0, QCoreApplication::translate("D3D11VAWidget", "DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL", nullptr));
        d3d11SwapEffect->setItemText(1, QCoreApplication::translate("D3D11VAWidget", "DXGI_SWAP_EFFECT_SEQUENTIAL", nullptr));
        d3d11SwapEffect->setItemText(2, QCoreApplication::translate("D3D11VAWidget", "DXGI_SWAP_EFFECT_FLIP_DISCARD", nullptr));
        d3d11SwapEffect->setItemText(3, QCoreApplication::translate("D3D11VAWidget", "DXGI_SWAP_EFFECT_DISCARD", nullptr));

    } // retranslateUi

};

namespace Ui {
    class D3D11VAWidget: public Ui_D3D11VAWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D3D11VAWIDGET_H
