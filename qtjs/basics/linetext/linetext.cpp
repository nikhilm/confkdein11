#include "linetext.h"

#include <QtScript>
#include <QApplication>
#include <QLineEdit>
#include <QDebug>

void Script::readText()
{
    QScriptEngine eng;
    QScriptValue lineEdit = eng.newQObject(QObject::sender());

    eng.globalObject().setProperty("lineEdit", lineEdit);

    QString value = eng.evaluate("lineEdit.text").toString();
    qDebug() << "Text is" << value;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QLineEdit edit("Default");
    edit.resize(200, 70);
    edit.show();

    Script s;

    QObject::connect(&edit, SIGNAL(returnPressed()), &s, SLOT(readText()));

    app.exec();
}
