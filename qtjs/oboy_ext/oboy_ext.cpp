#include "oboy_ext.h"

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

QScriptValue mapHeader(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue responseWrapper = context->thisObject();
    QHttpResponse *response = qobject_cast<QHttpResponse*>(responseWrapper.toQObject());

    if( context->argumentCount() < 1 )
        return context->throwError("Expected integer reply status");
    if( context->argumentCount() >= 2 )
    {
        QVariantMap headers = context->argument(1).toVariant().toMap();
        foreach(QString field, headers.keys())
            response->setHeader(field, headers[field].toString());
    }

    int status = context->argument(0).toUInt16();
    response->writeHead(status);

    return QScriptValue::UndefinedValue;
}

void Oboy::handle(QHttpRequest *req, QHttpResponse *res)
{
    QScriptEngine *engine = m_callback.engine();
    Q_ASSERT(engine);
    
    QScriptValue reqWrapper = engine->newQObject(req, QScriptEngine::ScriptOwnership);
    QScriptValue resWrapper = engine->newQObject(res, QScriptEngine::ScriptOwnership);

    resWrapper.setProperty("writeHead", engine->newFunction(mapHeader));

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
