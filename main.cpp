#include "DeviceSearcher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    DeviceSearcher d;
    QObject::connect(&d, SIGNAL(accepted()), &app, SLOT(quit()));
    d.show();

    app.exec();

    return 0;
}

