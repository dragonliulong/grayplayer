#include "GrayPlayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_NativeWindows);
    QApplication a(argc, argv);

    GrayPlayer grayPlayer;
    grayPlayer.show();

    return a.exec();
}
