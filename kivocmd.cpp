#include "kivocmd.h"

KivoCMD::KivoCMD(QObject *parent)
    : QObject(parent)
{
    app = QCoreApplication::instance();
}

void KivoCMD::run()
{
    quit();
}

void KivoCMD::quit()
{
    emit finished();
}

void KivoCMD::aboutToQuitApp() {}
