#include "oboy.h"

#include <QtScript>
#include <QHostAddress>
#include <QDebug>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

Oboy::Oboy(QScriptValue callback)
    : QObject(0)
    , m_callback(callback)
{
    m_server = new QHttpServer;
    connect(m_server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handle(QHttpRequest *, QHttpResponse *)));
}

Oboy::~Oboy()
{
    delete m_server;
    m_server = 0;
}

void Oboy::handle(QHttpRequest *req, QHttpResponse *res)
{
    QScriptEngine *engine = m_callback.engine();
    Q_ASSERT(engine);
    
    QScriptValue reqWrapper = engine->newQObject(req, QScriptEngine::ScriptOwnership);
    QScriptValue resWrapper = engine->newQObject(res, QScriptEngine::ScriptOwnership);

    qDebug() << "CALLING";
    m_callback.call(QScriptValue(), QScriptValueList() << reqWrapper << resWrapper);
}

void Oboy::listen(const QString &host, quint16 port)
{
    //TODO error checking
    m_server->listen(QHostAddress(host), port);
}

void Oboy::listen(quint16 port)
{
    m_server->listen(port);
}
