#include <QtScript>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine engine;
    const QString theProgram = 
        "Math.log(25);"
    ;

    QScriptValue v = false;
    qDebug() << "Valid?" << v.isValid();
    engine.setGlobalObject(v);
    qDebug() << engine.evaluate(theProgram).toString();
    qDebug() << engine.hasUncaughtException();
}
