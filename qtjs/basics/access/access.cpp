#include <QtScript>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine eng;

    QObject *onTheHeap = new QObject;
    onTheHeap->setObjectName("Arthur");

    QScriptValue repr = eng.newQObject(onTheHeap);

    //QScriptValue repr = eng.newQObject(onTheHeap, QScriptEngine::ScriptOwnership, QScriptEngine::ExcludeSlots);

    eng.globalObject().setProperty("object", repr);

    QString program = "print(object.objectName);object.deleteLater()";

    eng.evaluate(program);

    QTimer::singleShot(2000, &app, SLOT(quit()));
    app.exec();

    qDebug() << onTheHeap->objectName();
}
