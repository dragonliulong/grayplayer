/********************************************************************************
** Form generated from reading UI file 'CoderWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODERWIDGET_H
#define UI_CODERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoderWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *csdn;
    QLabel *github;
    QLabel *mail;
    QLabel *bilibili;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *csdnURL;
    QLabel *githubURL;
    QLabel *mailURL;
    QLabel *bilibiliURL;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *CoderWidget)
    {
        if (CoderWidget->objectName().isEmpty())
            CoderWidget->setObjectName(QString::fromUtf8("CoderWidget"));
        CoderWidget->resize(664, 578);
        horizontalLayout = new QHBoxLayout(CoderWidget);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        csdn = new QLabel(CoderWidget);
        csdn->setObjectName(QString::fromUtf8("csdn"));
        csdn->setMinimumSize(QSize(0, 45));
        csdn->setMaximumSize(QSize(1000, 45));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        csdn->setFont(font);
        csdn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(csdn);

        github = new QLabel(CoderWidget);
        github->setObjectName(QString::fromUtf8("github"));
        github->setMinimumSize(QSize(0, 45));
        github->setMaximumSize(QSize(1000, 45));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setItalic(false);
        github->setFont(font1);
        github->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(github);

        mail = new QLabel(CoderWidget);
        mail->setObjectName(QString::fromUtf8("mail"));
        mail->setMinimumSize(QSize(0, 45));
        mail->setMaximumSize(QSize(1000, 45));
        mail->setFont(font);
        mail->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(mail);

        bilibili = new QLabel(CoderWidget);
        bilibili->setObjectName(QString::fromUtf8("bilibili"));
        bilibili->setMinimumSize(QSize(0, 45));
        bilibili->setMaximumSize(QSize(1000, 45));
        bilibili->setFont(font);
        bilibili->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(bilibili);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        csdnURL = new QLabel(CoderWidget);
        csdnURL->setObjectName(QString::fromUtf8("csdnURL"));
        csdnURL->setMinimumSize(QSize(0, 45));
        csdnURL->setMaximumSize(QSize(1000, 45));
        csdnURL->setFont(font);

        verticalLayout_2->addWidget(csdnURL);

        githubURL = new QLabel(CoderWidget);
        githubURL->setObjectName(QString::fromUtf8("githubURL"));
        githubURL->setMinimumSize(QSize(0, 45));
        githubURL->setMaximumSize(QSize(1000, 45));
        githubURL->setFont(font);
        githubURL->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(githubURL);

        mailURL = new QLabel(CoderWidget);
        mailURL->setObjectName(QString::fromUtf8("mailURL"));
        mailURL->setMinimumSize(QSize(0, 45));
        mailURL->setMaximumSize(QSize(1000, 45));
        mailURL->setFont(font);

        verticalLayout_2->addWidget(mailURL);

        bilibiliURL = new QLabel(CoderWidget);
        bilibiliURL->setObjectName(QString::fromUtf8("bilibiliURL"));
        bilibiliURL->setMinimumSize(QSize(0, 45));
        bilibiliURL->setMaximumSize(QSize(1000, 45));
        bilibiliURL->setFont(font);

        verticalLayout_2->addWidget(bilibiliURL);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        retranslateUi(CoderWidget);

        QMetaObject::connectSlotsByName(CoderWidget);
    } // setupUi

    void retranslateUi(QWidget *CoderWidget)
    {
        CoderWidget->setWindowTitle(QCoreApplication::translate("CoderWidget", "Form", nullptr));
        csdn->setText(QCoreApplication::translate("CoderWidget", "csdn", nullptr));
        github->setText(QCoreApplication::translate("CoderWidget", "github", nullptr));
        mail->setText(QCoreApplication::translate("CoderWidget", "\351\202\256\347\256\261", nullptr));
        bilibili->setText(QCoreApplication::translate("CoderWidget", "bilibili", nullptr));
        csdnURL->setText(QCoreApplication::translate("CoderWidget", "csdnURL", nullptr));
        githubURL->setText(QCoreApplication::translate("CoderWidget", "githubURL", nullptr));
        mailURL->setText(QCoreApplication::translate("CoderWidget", "mailURL", nullptr));
        bilibiliURL->setText(QCoreApplication::translate("CoderWidget", "bilibiliURL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoderWidget: public Ui_CoderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODERWIDGET_H
