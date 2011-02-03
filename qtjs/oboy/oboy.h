#ifndef OBOY
#define OBOY

#include <QtScript>

class QHttpServer;
class QHttpRequest;
class QHttpResponse;

class Oboy : public QObject
{
    Q_OBJECT
public:
    Oboy(QScriptValue callback);
    ~Oboy();
    Q_INVOKABLE void listen(const QString &host, quint16 port);
    Q_INVOKABLE void listen(quint16 port);

private slots:
    void handle(QHttpRequest *req, QHttpResponse *res);

private:
    QScriptValue m_callback;
    QHttpServer *m_server;
};

#endif
