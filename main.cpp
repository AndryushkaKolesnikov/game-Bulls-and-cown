#include "bullsandcown.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BullsAndCown w;
    w.show();
    return a.exec();
}
