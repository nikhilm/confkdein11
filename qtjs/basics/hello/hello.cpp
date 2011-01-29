#include <QtScript>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine engine;
    const QString theProgram = 
        "var event = function() {"
        "    return 'Welcome to Conf.KDE.in 2011!';"
        "}\n"
        "event()"
    ;

    qDebug() << engine.evaluate(theProgram).toString();
}
