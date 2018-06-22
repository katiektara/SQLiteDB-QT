#include "university.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    University w;
    w.show();

    return a.exec();
}
