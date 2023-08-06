#ifndef KIVOCMD_H
#define KIVOCMD_H

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QObject>
#include <QTextStream>

using namespace std;

class KivoCMD : public QObject
{
    Q_OBJECT

private:
    QCoreApplication *app;

public:
    explicit KivoCMD(QObject *parent = 0);
    void quit();

signals:
    void finished();

public slots:
    void run();
    void aboutToQuitApp();
};

#endif // KIVOCMD_H
