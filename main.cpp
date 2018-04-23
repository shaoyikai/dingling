#include "dingling.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DingLing w;
    w.show();

    return a.exec();
}
