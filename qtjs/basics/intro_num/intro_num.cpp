#include <QtScript>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine engine;
    engine.globalObject().setProperty("theAnswer", QScriptValue(42));

    qDebug() << engine.evaluate("theAnswer").toInteger();
}
