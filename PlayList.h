#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <Button.h>
#include <QListView>
#include <QLabel>
#include <string>
#include <map>
#include <QStandardItemModel>
#include <LineEdit.h>
using namespace std;

namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(QWidget *parent = nullptr);
    ~PlayList();
    void setLeftAddInfo(CustomInfo*,bool cur=true);
    void setRightAddInfo(CustomInfo*,bool cur=false);
    Button* getAddButton();
    QPushButton* getLeftOpt();
    QPushButton* getRightOpt();
    Button* getBackButton();
    QLabel* getTitle();

public slots:
    void leftOptClick();
    void rightOptClick();
    void addFile(char* file=NULL);
    void addUrl(QString);
    void removeFile();

signals:
    void requestStopPlay(int);
    void requestPlayPrepare(int);
    void open(char*);
    void error(int);

public slots:
    void playStopFinish(int);
    void playPrepareFinish(int);
    void playBefore();
    void playNext();
    void playRepeat();
    void itemDoubleClick(const QModelIndex&);

private:
    Ui::PlayList* ui;
    QListView* rightList;
    CustomInfo leftAddInfo;
    CustomInfo rightAddInfo;
    QStandardItemModel leftModel, rightModel;
    LineEdit* lineEdit;

private:
    map<QString,bool> leftExist, rightExist;

private:
    void readIni();
    int findInLeftList(QString);

private:
    void getShowTypes();
    string showTypes;
    QByteArray fileNameCur;
    int videoFileCount;

protected:
    void paintEvent(QPaintEvent*);
    void contextMenuEvent(QContextMenuEvent*);
};

#endif // PLAYLIST_H
