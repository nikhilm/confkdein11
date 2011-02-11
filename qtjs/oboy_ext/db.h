#ifndef SCRIPT_DB_H
#define SCRIPT_DB_H

#include <QtScript>
#include <QtSql>

class DB : public QObject
{
    Q_OBJECT
public:
    DB(const QString &dbName, QScriptEngine *engine);
    ~DB();

public slots:
    Q_INVOKABLE QScriptValue get(const QString &tblName);
    Q_INVOKABLE QScriptValue getWhere(const QString &tblName, QVariantMap map);
    Q_INVOKABLE QScriptValue insert(const QString &tblName, QVariantMap map);
    Q_INVOKABLE QScriptValue update(const QString &tblName, QVariantMap map, QVariantMap conditions);

    bool isOpen() const { return m_db.isOpen(); };

private:
    QHash<QString, QString> m_assoc;
    QSqlDatabase m_db;
    QString m_curQuery;
    QScriptEngine *m_engine;
};

class QueryWrapper : public QObject, public QScriptClass
{
    Q_OBJECT
public:
    QueryWrapper(QSqlQuery *q, QScriptEngine *engine);
    ~QueryWrapper();
    QueryFlags queryProperty(const QScriptValue &object, const QScriptString &name, QueryFlags flags, uint *id);
    QScriptValue property(const QScriptValue &object, const QScriptString &name, uint id);
private:
    QSqlQuery *m_q;
};

#endif
