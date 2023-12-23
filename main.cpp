#include <QCoreApplication>
#include "mainObject.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MainObject obj;
    return app.exec();
}
