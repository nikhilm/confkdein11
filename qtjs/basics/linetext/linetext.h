#include <QObject>

class Script : public QObject
{
    Q_OBJECT
public slots:
    void readText();
};
