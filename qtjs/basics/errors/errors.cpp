#include <QtScript>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine engine;

    QFile f(app.applicationDirPath() + "/calculator.js");
    f.open(QFile::ReadOnly);

    QString theProgram = QTextStream(&f).readAll();
    theProgram += "calculate('1/0');";

    qDebug() << engine.evaluate(theProgram, "calculator.js").toNumber();

    qDebug() << "Error?" << engine.hasUncaughtException();
    qDebug() << engine.uncaughtException().property("message").toString();
    qDebug() << "On line number" << engine.uncaughtExceptionLineNumber();
    qDebug() << "Backtrace: " << engine.uncaughtExceptionBacktrace();
}
