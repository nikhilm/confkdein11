#include <QTimerEvent>
#include <QScriptEngine>
#include <QObject>

class Timeout : public QObject
{
    Q_OBJECT
public:
    void runTheScript();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QScriptEngine m_engine;
};
