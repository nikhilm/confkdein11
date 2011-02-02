#include <QtScript>
#include <QApplication>
#include <QLineEdit>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QLineEdit edit("Default");
    edit.resize(200, 70);
    edit.show();

    QScriptEngine eng;
    QScriptValue lineEdit = eng.newQObject(&edit);

    eng.globalObject().setProperty("lineEdit", lineEdit);

    QString program = "lineEdit.returnPressed.connect(function() { print('You typed: ' + lineEdit.text); });";

    eng.evaluate(program);

    app.exec();
}
