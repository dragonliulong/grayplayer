#include "PlayList.h"
#include "ui_PlayList.h"
#include <QDebug>
#include <QScrollBar>
#include <QSettings>
#include <QFileDialog>
#include <QContextMenuEvent>
#include <QMenu>
#include "StandardItem.h"
#include "MultimediaType.h"

PlayList::PlayList(QWidget* parent):
    QWidget(parent),
    ui(new Ui::PlayList),
    videoFileCount(0)
{
    ui->setupUi(this);
    getShowTypes();

    //鼠标跟踪
    setMouseTracking(true);

    //返回按钮
    CustomInfo backInfo;
    backInfo.dy = false;
    backInfo.text0 = "返回";
    ui->back->setFont(QFont("微软雅黑",8));
    ui->back->initCustom(&backInfo);

    //add
    ui->add->setFont(QFont("微软雅黑",12,20));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(addFile()));

    //widget
    ui->widget->setStyleSheet("background:rgb(30,30,45);");

    //rightList
    rightList = new QListView(this);
    rightList->hide();

    //opt
    connect(ui->leftOpt,&QPushButton::clicked,this,&PlayList::leftOptClick);
    connect(ui->rightOpt,&QPushButton::clicked,this,&PlayList::rightOptClick);

    ui->leftOpt->setFlat(true);
    ui->rightOpt->setFlat(true);
    ui->leftOpt->setFont(QFont("微软雅黑",8));
    ui->rightOpt->setFont(QFont("微软雅黑",8));

    ui->leftOpt->setStyleSheet("color:rgb(250,250,250); background:rgb(30,30,45); border:1px rgb(30,30,45) solid;");
    ui->rightOpt->setStyleSheet("color:rgb(200,200,200); background:rgb(20,20,30); border:1px rgb(20,20,30) solid;");

    //scrollBar
    ui->leftList->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{ background:black; width:10px }"
                                                     "QScrollBar::sub-page:vertical{ background:rgb(20,20,30) }"
                                                     "QScrollBar::add-page:vertical{ background:rgb(20,20,30) }"
                                                     "QScrollBar::sub-line:vertical{ height:0px }"
                                                     "QScrollBar::add-line:vertical{ height:0px }"
                                                     "QScrollBar::handle:vertical{ background:rgb(60,60,80); border-radius:5px; top:5px; bottom:5px }");

    rightList->verticalScrollBar()->setStyleSheet(ui->leftList->verticalScrollBar()->styleSheet());

    //lineEdit
    lineEdit = new LineEdit();
    lineEdit->hide();
    connect(lineEdit,&LineEdit::acceptUrlNow,this,&PlayList::addUrl);

    //listView
    readIni();
    ui->leftList->setModel(&leftModel);
    rightList->setModel(&rightModel);

    connect(ui->leftList,&QListView::doubleClicked,this,&PlayList::itemDoubleClick);
    connect(rightList,&QListView::doubleClicked,this,&PlayList::itemDoubleClick);
}

void PlayList::leftOptClick()
{
    ui->leftOpt->setStyleSheet("color:rgb(250,250,250); background:rgb(30,30,45); border:1px rgb(30,30,45) solid;");
    ui->rightOpt->setStyleSheet("color:rgb(200,200,200); background:rgb(20,20,30); border:1px rgb(20,20,30) solid;");
    ui->add->initCustom(&leftAddInfo);

    //替换listView
    ui->widget->layout()->replaceWidget(rightList, ui->leftList);
    ui->leftList->show();
    rightList->hide();
}

void PlayList::rightOptClick()
{
    ui->rightOpt->setStyleSheet("color:rgb(250,250,250); background:rgb(30,30,45); border:1px rgb(30,30,45) solid;");
    ui->leftOpt->setStyleSheet("color:rgb(200,200,200); background:rgb(20,20,30); border:1px rgb(20,20,30) solid;");
    ui->add->initCustom(&rightAddInfo);

    //替换listView
    ui->widget->layout()->replaceWidget(ui->leftList, rightList);
    rightList->show();
    ui->leftList->hide();
}

void PlayList::readIni()
{
    QString path = QCoreApplication::applicationDirPath() + "/playList.ini";
    QSettings setting(path, QSettings::IniFormat);

    videoFileCount = 0;

    if(setting.value("launch/first", true).toBool()) setting.setValue("launch/first",false);
    else
    {
        QStringList localList, netList;
        localList = setting.value("lists/local",QStringList()).toStringList();
        netList = setting.value("lists/net",QStringList()).toStringList();

        //本地
        for(int i=0; i < localList.size(); i++)
        {
            if(!leftExist[localList[i]])
            {
                leftExist[localList[i]] = true;
                StandardItem* item = new StandardItem(localList[i]);

                if(item->getType() == VIDEO_TYPE)
                {
                    leftModel.insertRow(videoFileCount, item);
                    videoFileCount++;
                }
                else
                {
                    leftModel.appendRow(item);
                }
            }
        }

        //网络
        for(int i=0; i < netList.size(); i++)
        {
            if(!rightExist[netList[i]])
            {
                rightExist[netList[i]] = true;
                StandardItem* item = new StandardItem(netList[i]);
                rightModel.appendRow(item);
            }
        }
    }
}

PlayList::~PlayList()
{
    QString path = QCoreApplication::applicationDirPath() + "/playList.ini";
    QSettings setting(path, QSettings::IniFormat);

    setting.setValue("launch/first",false);

    QStringList localList, netList;

    for(int i=0; i < leftModel.rowCount(); i++)
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(i));
        localList.push_back(item->getFileName());
    }

    for(int i=0; i< rightModel.rowCount(); i++)
    {
        StandardItem* item = static_cast<StandardItem*>(rightModel.item(i));
        netList.push_back(item->getFileName());
    }

    setting.setValue("lists/local",localList);
    setting.setValue("lists/net",netList);

    delete ui;
}

void PlayList::addFile(char* file)
{
    if(file == NULL)
    {
        if(ui->leftList->isVisible())
        {
            //添加本地文件
            QByteArray fileName = QFileDialog::getOpenFileName(this, tr("打开本地文件"), tr(""), tr(showTypes.c_str())).toUtf8();

            if(fileName.size() > 0)
            {
                QString fileNameString(fileName);

                if(!leftExist[fileNameString])
                {
                    leftExist[fileNameString] = true;
                    StandardItem* item = new StandardItem(fileNameString);

                    if(item->getType() == VIDEO_TYPE)
                    {
                        leftModel.insertRow(videoFileCount, item);
                        videoFileCount++;
                    }
                    else
                    {
                        leftModel.appendRow(item);
                    }
                }
            }
        }
        else
        {
            //添加网络流
            QPoint p = parentWidget()->pos();
            int x = (parentWidget()->width() - lineEdit->width())/2 + parentWidget()->mapToGlobal(p).x();
            int y = (parentWidget()->height() - lineEdit->height())/2 + parentWidget()->mapToGlobal(p).y();
            lineEdit->move(x,y);
            lineEdit->show();
        }
    }
    else
    {
        //直接添加本地文件
        QString fileNameString(file);

        if(!leftExist[fileNameString])
        {
            leftExist[fileNameString] = true;
            StandardItem* item = new StandardItem(fileNameString);

            if(item->getType() == VIDEO_TYPE)
            {
                leftModel.insertRow(videoFileCount, item);
                videoFileCount++;
            }
            else
            {
                leftModel.appendRow(item);
            }
        }
    }
}

void PlayList::addUrl(QString url)
{
    if(!rightExist[url])
    {
        rightExist[url] = true;
        StandardItem* item = new StandardItem(url);
        rightModel.appendRow(item);
    }
}

void PlayList::removeFile()
{
    if(ui->leftList->isVisible())
    {
        QModelIndex index = ui->leftList->currentIndex();
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(index.row()));
        if(item->getType() == VIDEO_TYPE) videoFileCount--;

        leftExist[item->getFileName()] = false;
        leftModel.removeRow(index.row());
    }
    else
    {
        QModelIndex index = rightList->currentIndex();
        StandardItem* item = static_cast<StandardItem*>(rightModel.item(index.row()));

        rightExist[item->getFileName()] = false;
        rightModel.removeRow(index.row());
    }
}

void PlayList::playStopFinish(int f)
{
    if(f != 1) return;

    if(fileNameCur.size() > 0)
    {
        set_multimedia_type(fileNameCur.data(), NULL);
        emit requestPlayPrepare(1);
    }
}

void PlayList::playPrepareFinish(int f)
{
    if(f != 1) return;

    if(fileNameCur.size() > 0)
    {
        emit open(fileNameCur.data());
    }
}

void PlayList::itemDoubleClick(const QModelIndex& index)
{
    if(ui->leftList->isVisible())
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(index.row()));
        fileNameCur = item->getFileName().toUtf8();
        emit requestStopPlay(1);
    }
    else
    {
        StandardItem* item = static_cast<StandardItem*>(rightModel.item(index.row()));
        fileNameCur = item->getFileName().toUtf8();
        emit requestStopPlay(1);
    }
}

void PlayList::playNext()
{
    int i = -1;

    if(fileNameCur.size() > 0 && leftExist[fileNameCur])
        i = findInLeftList(fileNameCur) + 1;

    if(i >= 0 && i < leftModel.rowCount())
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(i));
        fileNameCur = item->getFileName().toUtf8();
        emit requestStopPlay(1);
    }
    else
    {
        fileNameCur.clear();
        emit requestStopPlay(1);
        emit error(-1);
    }
}

void PlayList::playRepeat()
{
    int i = -1;

    if(fileNameCur.size() > 0 && leftExist[fileNameCur])
        i = findInLeftList(fileNameCur);

    if(i >= 0 && i < leftModel.rowCount())
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(i));
        fileNameCur = item->getFileName().toUtf8();
        emit requestStopPlay(1);
    }
    else
    {
        fileNameCur.clear();
        emit requestStopPlay(1);
        emit error(-1);
    }
}

void PlayList::playBefore()
{
    int i = -1;

    if(fileNameCur.size() > 0 && leftExist[fileNameCur])
        i = findInLeftList(fileNameCur) - 1;

    if(i >= 0 && i < leftModel.rowCount())
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(i));
        fileNameCur = item->getFileName().toUtf8();
        emit requestStopPlay(1);
    }
    else
    {
        fileNameCur.clear();
        emit requestStopPlay(1);
        emit error(-1);
    }
}

void PlayList::getShowTypes()
{
    QString typeString;

    for(int i=0; i < (int)audioTypes.size(); i++)
    {
        if(i!=0) typeString += " ";
        typeString += "*.";
        typeString += QString::fromStdString(audioTypes[i]);
    }

    for(int i=0; i < (int)videoTypes.size(); i++)
    {
        typeString += " ";
        typeString += "*.";
        typeString += QString::fromStdString(videoTypes[i]);
    }

    showTypes = QString("视频和音频类型(%1)").arg(typeString).toStdString();
}

int PlayList::findInLeftList(QString s)
{
    for(int i=0; i < leftModel.rowCount(); i++)
    {
        StandardItem* item = static_cast<StandardItem*>(leftModel.item(i));
        if(s == item->getFileName()) return i;
    }

    return -1;
}

void PlayList::setLeftAddInfo(CustomInfo* info, bool cur)
{
    leftAddInfo.dy = info->dy;
    leftAddInfo.text0 = info->text0;
    leftAddInfo.text1 = info->text1;
    leftAddInfo.tip0 = info->tip0;
    leftAddInfo.tip1 = info->tip1;

    if(cur) ui->add->initCustom(&leftAddInfo);
}

void PlayList::setRightAddInfo(CustomInfo* info, bool cur)
{
    rightAddInfo.dy = info->dy;
    rightAddInfo.text0 = info->text0;
    rightAddInfo.text1 = info->text1;
    rightAddInfo.tip0 = info->tip0;
    rightAddInfo.tip1 = info->tip1;

    if(cur) ui->add->initCustom(&rightAddInfo);
}

Button* PlayList::getAddButton()
{
    return ui->add;
}

QPushButton* PlayList::getLeftOpt()
{
    return ui->leftOpt;
}

QPushButton* PlayList::getRightOpt()
{
    return ui->rightOpt;
}

Button* PlayList::getBackButton()
{
    return ui->back;
}

QLabel* PlayList::getTitle()
{
    return ui->title;
}

void PlayList::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PlayList::contextMenuEvent(QContextMenuEvent* e)
{
    QStandardItem* item = NULL;

    if(ui->leftList->isVisible())
    {
        QModelIndex index = ui->leftList->indexAt(ui->leftList->mapFromGlobal(e->globalPos()));
        item = leftModel.item(index.row());
    }
    else
    {
        QModelIndex index = rightList->indexAt(rightList->mapFromGlobal(e->globalPos()));
        item = rightModel.item(index.row());
    }

    if(!item) return;

    QMenu menu;
    menu.addAction(tr("删除"),this,&PlayList::removeFile);
    menu.exec(e->globalPos());
}
