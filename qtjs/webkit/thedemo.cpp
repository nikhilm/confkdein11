#include "thedemo.h"

#include <QFile>
#include <QTextStream>
#include <QtWebKit>

TheDemo::TheDemo(QObject *parent)
    : QObject(parent)
    , m_frame(0)
{
}

TheDemo::~TheDemo()
{
}

QPixmap TheDemo::smiley()
{
    QPixmap pixmap(200, 200);
    pixmap.fill();

    QPainter p(&pixmap);

    QPen pen(QBrush(Qt::black), 10, Qt::SolidLine, Qt::RoundCap);
    p.setPen(pen);

    p.setBrush(QBrush(Qt::yellow));
    p.drawEllipse(10, 10, 180, 180);

    p.setBrush(QBrush(Qt::white));
    p.drawChord(50, 70, 100, 100, 195*16, 150*16);

    p.drawEllipse(50, 50, 30, 30);
    p.drawEllipse(120, 50, 30, 30);
    p.setBrush(QBrush(Qt::black));
    p.drawEllipse(65, 65, 10, 10);
    p.drawEllipse(135, 65, 10, 10);

    return pixmap;
}

void TheDemo::promoteQt()
{
    QWebElement p = m_frame->documentElement().findFirst("p#blurb");
    QString orig = p.toInnerXml();
    QString repl = orig.replace("qt", "<strong>Qt</strong>", Qt::CaseInsensitive);
    QWebElement p2 = m_frame->documentElement().findFirst("p#blank");
    p2.setInnerXml(repl);
}

void TheDemo::inject()
{
    m_frame = qobject_cast<QWebFrame*>(QObject::sender());
    m_frame->addToJavaScriptWindowObject("theDemo", this);
}
