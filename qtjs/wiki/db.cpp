#include "db.h"

#include <QDebug>

DB::DB(const QString &dbName, QScriptEngine *engine)
    : QObject(0)
    , m_engine(engine)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);
    m_db.open();
}

DB::~DB()
{
    m_db.close();
}

QScriptValue DB::get(const QString &tblName)
{
    // TODO: use the engine to evaluate all this so that we can use the
    // generated bindings
    QSqlQuery *query = new QSqlQuery(QString("SELECT * FROM %1;").arg(tblName));
    query->exec();
    return m_engine->newObject(new QueryWrapper(query, m_engine), QScriptEngine::ScriptOwnership);
}

QScriptValue DB::getWhere(const QString &tblName, QVariantMap map)
{
    QString queryString = QString("SELECT * FROM %1 WHERE ").arg(tblName);

    QStringList bits;
    foreach(QString key, map.keys())
        bits << (key + "='" + map[key].toString() + "'");
    queryString += bits.join(" AND ");
    queryString += ";";

    QSqlQuery *query = new QSqlQuery(queryString);
    query->exec();
    return m_engine->newObject(new QueryWrapper(query, m_engine), QScriptEngine::ScriptOwnership);
}

QScriptValue DB::insert(const QString &tblName, QVariantMap map)
{
    QString queryString = QString("INSERT INTO %1 (").arg(tblName);
    queryString += QStringList(map.keys()).join(", ");

    queryString += ") VALUES (" + QStringList(QVector<QString>(map.size(), "?").toList()).join(", ") + ");";
    // qmap guarantees keys() and values() to return same order

    QSqlQuery q(queryString);
    foreach(QVariant value, map.values())
        q.addBindValue(value.toString());

    return QScriptValue(q.exec());
}

QScriptValue DB::update(const QString &tblName, QVariantMap map, QVariantMap conditions)
{
    QString queryString = QString("UPDATE %1 SET ").arg(tblName);
    QStringList keys;
    foreach(QString key, map.keys())
        keys << (key + "=?");
    queryString += keys.join(", ");

    if( conditions.size() > 0 ) {
        queryString += " WHERE ";

        QStringList bits;
        foreach(QString key, conditions.keys())
            bits << (key + "='" + conditions[key].toString() + "'");
        queryString += bits.join(" AND ");
    }
    queryString += ";";
    QSqlQuery q(queryString);
    foreach(QVariant value, map.values())
        q.addBindValue(value.toString());

    return QScriptValue(q.exec());
}

//------------- QueryWrapper --------------
QueryWrapper::QueryWrapper(QSqlQuery *q, QScriptEngine *engine)
    : QObject(0)
    , QScriptClass(engine)
    , m_q(q)
{
}

QueryWrapper::~QueryWrapper()
{
    delete m_q;
    m_q = 0;
}

QScriptValue QueryWrapper::property(const QScriptValue &object, const QScriptString &name, uint id)
{
    QString property = name.toString();
    if( property == "next" )
        return QScriptValue(m_q->next());
    else {
        QSqlRecord record = m_q->record();
        QVariant val = record.value(property);
        return engine()->newVariant(val);
    }
}

QueryWrapper::QueryFlags QueryWrapper::queryProperty(const QScriptValue &object, const QScriptString &name, QueryFlags flags, uint *id)
{
    QString property = name.toString();
    if( property == "next" )
        return HandlesReadAccess;
    return HandlesReadAccess | HandlesWriteAccess;
}
