#include <QtScript>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget w;

    QVBoxLayout *layout = new QVBoxLayout;
    QLineEdit edit("Default");
    layout->addWidget(&edit);

    QPushButton btn("Press Me");
    layout->addWidget(&btn);

    QScriptEngine eng;
    QScriptValue lineEdit = eng.newQObject(&edit);
    QScriptValue btnScript = eng.newQObject(&btn);

    eng.globalObject().setProperty("lineEdit", lineEdit);
    eng.globalObject().setProperty("button", btnScript);

    QString program = "lineEdit.returnPressed.connect(lineEdit, function() { print('You typed: ' + this.text); });"
                      "button.clicked.connect(function() { lineEdit.returnPressed(); })";

    eng.evaluate(program);

    w.setLayout(layout);
    w.show();
    app.exec();
}
