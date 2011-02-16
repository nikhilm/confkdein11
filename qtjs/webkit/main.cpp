#include <QApplication>
#include <QtWebKit>

#include "thedemo.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWebView *view = new QWebView;
    view->load(QUrl("file://" + app.applicationDirPath() + "/driver.html"));
    view->resize(1280, 700);

    QWebFrame *theFrame = view->page()->currentFrame();
    view->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    TheDemo *demo = new TheDemo;

    QObject::connect(theFrame, SIGNAL(javaScriptWindowObjectCleared()), demo, SLOT(inject()));
    view->show();
    app.exec();
}
