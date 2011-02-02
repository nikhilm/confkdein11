#include <QtScript>
#include <QCoreApplication>
#include <QLineEdit>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QScriptEngine eng;

    QObject parent;

    QObject child(&parent);
    child.setObjectName("child");
    child.setProperty("name", QVariant("JavaScript"));

    eng.globalObject().setProperty("parent", eng.newQObject(&parent));

    QString program = "print(parent.child.name)";

    eng.evaluate(program);
}
