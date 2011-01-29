#include "timeout.h"

#include <QtScript>
#include <QCoreApplication>
#include <QDebug>

void Timeout::runTheScript()
{
    m_engine.setProcessEventsInterval(100);

    startTimer(5000);

    const QString theProgram = "while(1); 5";

    qDebug() << "Running program...";
    qDebug() << m_engine.evaluate(theProgram).toString();
}

void Timeout::timerEvent(QTimerEvent *event)
{
    qDebug() << "Script is running for more than 5 seconds. Killing it and quitting";
    m_engine.abortEvaluation(QScriptValue::UndefinedValue);
    QCoreApplication::quit();
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    Timeout t;
    t.runTheScript();
}
