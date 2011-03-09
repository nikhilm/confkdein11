#include <QCoreApplication>
#include <QStringList>
#include <QtScript>
#include <QDebug>

#include "oboy_headers.h"

typedef QHash<QString, QString> HeaderHash;
Q_DECLARE_METATYPE(HeaderHash);

template <typename HeaderHash>
QScriptValue headersToScriptValue(QScriptEngine *engine, const HeaderHash &headers)
{
    QScriptValue val = engine->newObject();
    foreach(QString key, headers.keys())
        val.setProperty(key, QScriptValue(headers[key]));
    return val;
}

template <typename HeaderHash>
void headersFromScriptValue(const QScriptValue &value, HeaderHash &t)
{
    Q_UNUSED(value);
    Q_UNUSED(t);
}

QScriptValue createServer(QScriptContext *context, QScriptEngine *engine)
{
    if( context->argumentCount() < 1 )
        return context->throwError("Expected server handler callback as first argument");

    if( !context->argument(0).isFunction() )
        return context->throwError("Expected function as first argument");

    Oboy *server = new Oboy(context->argument(0));
    qScriptRegisterMetaType<HeaderHash>(engine, headersToScriptValue, headersFromScriptValue);
    QScriptValue wrapper = engine->newQObject(server, QScriptEngine::ScriptOwnership);

    return wrapper;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QTextStream err(stderr);

    QStringList arguments = app.arguments();
    if( arguments.length() < 2 )
    {
        err << QString("USAGE: %1 <script>\n").arg(arguments[0]);

        return 1;
    }

    QScriptEngine engine;
    
    engine.globalObject().setProperty("createServer", engine.newFunction(createServer));

    QFile file(arguments[1]);
    if( !file.open(QFile::ReadOnly) )
    {
        err << QString("Error opening %1: %2\n").arg(arguments[1]).arg(file.errorString());
        return 2;
    }

    QTextStream reader(&file);
    engine.evaluate(reader.readAll(), arguments[1]);

    if( engine.hasUncaughtException() )
    {
        err << "Exception\n";
        err << engine.uncaughtException().property("message").toString() << "\n";
        err << "On line number " << engine.uncaughtExceptionLineNumber() << "\n";
        err << "Backtrace:\n";
        foreach(QString s, engine.uncaughtExceptionBacktrace())
            err << "    " << s << "\n";
        return 3;
    }

    app.exec();
}
