/********************************************************************************
** Form generated from reading UI file 'GrayPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAYPLAYER_H
#define UI_GRAYPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Button.h"
#include "VideoArea.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topLayout;
    QLabel *title;
    QSpacerItem *horizontalSpacer_3;
    Button *setting;
    Button *min;
    Button *max;
    Button *exit;
    QHBoxLayout *centralLayout;
    VideoArea *videoArea;
    Button *open;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer_2;
    Button *before;
    Button *play;
    Button *next;
    QSpacerItem *horizontalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(981, 587);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(20, 20, 28);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        topLayout = new QHBoxLayout();
        topLayout->setSpacing(2);
        topLayout->setObjectName(QString::fromUtf8("topLayout"));
        topLayout->setContentsMargins(12, 12, 12, 12);
        title = new QLabel(centralWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(150, 45));
        title->setMaximumSize(QSize(150, 45));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(15);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        title->setFont(font);
        title->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);"));

        topLayout->addWidget(title);

        horizontalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topLayout->addItem(horizontalSpacer_3);

        setting = new Button(centralWidget);
        setting->setObjectName(QString::fromUtf8("setting"));
        setting->setMinimumSize(QSize(45, 40));
        setting->setMaximumSize(QSize(45, 40));

        topLayout->addWidget(setting);

        min = new Button(centralWidget);
        min->setObjectName(QString::fromUtf8("min"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(min->sizePolicy().hasHeightForWidth());
        min->setSizePolicy(sizePolicy);
        min->setMinimumSize(QSize(45, 40));
        min->setMaximumSize(QSize(45, 40));
        min->setStyleSheet(QString::fromUtf8(""));
        min->setFlat(false);

        topLayout->addWidget(min);

        max = new Button(centralWidget);
        max->setObjectName(QString::fromUtf8("max"));
        sizePolicy.setHeightForWidth(max->sizePolicy().hasHeightForWidth());
        max->setSizePolicy(sizePolicy);
        max->setMinimumSize(QSize(45, 40));
        max->setMaximumSize(QSize(45, 40));
        max->setStyleSheet(QString::fromUtf8(""));
        max->setFlat(false);

        topLayout->addWidget(max);

        exit = new Button(centralWidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        sizePolicy.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy);
        exit->setMinimumSize(QSize(45, 40));
        exit->setMaximumSize(QSize(45, 40));
        exit->setStyleSheet(QString::fromUtf8(""));
        exit->setFlat(false);

        topLayout->addWidget(exit);

        topLayout->setStretch(0, 20);
        topLayout->setStretch(3, 1);
        topLayout->setStretch(4, 1);
        topLayout->setStretch(5, 1);

        verticalLayout->addLayout(topLayout);

        centralLayout = new QHBoxLayout();
        centralLayout->setSpacing(0);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
        centralLayout->setContentsMargins(-1, -1, -1, 0);
        videoArea = new VideoArea(centralWidget);
        videoArea->setObjectName(QString::fromUtf8("videoArea"));
        videoArea->setMinimumSize(QSize(0, 0));
        open = new Button(videoArea);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(420, 230, 140, 70));
        sizePolicy.setHeightForWidth(open->sizePolicy().hasHeightForWidth());
        open->setSizePolicy(sizePolicy);
        open->setMinimumSize(QSize(140, 70));
        open->setMaximumSize(QSize(140, 70));
        open->setLayoutDirection(Qt::LeftToRight);

        centralLayout->addWidget(videoArea);


        verticalLayout->addLayout(centralLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setSpacing(7);
        bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));
        bottomLayout->setContentsMargins(-1, 15, -1, 15);
        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomLayout->addItem(horizontalSpacer_2);

        before = new Button(centralWidget);
        before->setObjectName(QString::fromUtf8("before"));
        sizePolicy.setHeightForWidth(before->sizePolicy().hasHeightForWidth());
        before->setSizePolicy(sizePolicy);
        before->setMinimumSize(QSize(50, 45));
        before->setMaximumSize(QSize(50, 45));

        bottomLayout->addWidget(before);

        play = new Button(centralWidget);
        play->setObjectName(QString::fromUtf8("play"));
        sizePolicy.setHeightForWidth(play->sizePolicy().hasHeightForWidth());
        play->setSizePolicy(sizePolicy);
        play->setMinimumSize(QSize(50, 45));
        play->setMaximumSize(QSize(50, 45));
        play->setStyleSheet(QString::fromUtf8(""));
        play->setFlat(false);

        bottomLayout->addWidget(play);

        next = new Button(centralWidget);
        next->setObjectName(QString::fromUtf8("next"));
        sizePolicy.setHeightForWidth(next->sizePolicy().hasHeightForWidth());
        next->setSizePolicy(sizePolicy);
        next->setMinimumSize(QSize(50, 45));
        next->setMaximumSize(QSize(50, 45));

        bottomLayout->addWidget(next);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomLayout->addItem(horizontalSpacer);

        bottomLayout->setStretch(0, 10);
        bottomLayout->setStretch(1, 3);
        bottomLayout->setStretch(2, 3);
        bottomLayout->setStretch(3, 3);
        bottomLayout->setStretch(4, 10);

        verticalLayout->addLayout(bottomLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 8);
        verticalLayout->setStretch(2, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "  grayplayer", nullptr));
        setting->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        min->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        max->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        before->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252", nullptr));
        play->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAYPLAYER_H
