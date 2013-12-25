#include <QApplication>
#include "dialog.h"

#include "hsv2rgb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;

    init_hsv2rgb();
    w.show();
    
    return a.exec();
}
