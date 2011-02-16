#ifndef THEDEMO_H
#define THEDEMO_H

#include <QObject>
#include <QPixmap>

class QWebFrame;

class TheDemo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int answer READ answer CONSTANT);
public:
    TheDemo(QObject *parent=0);
    ~TheDemo();

    int answer() { return 42; }

    Q_INVOKABLE QPixmap smiley();

public slots:
    void inject();

private:
    QWebFrame *m_frame;
};

#endif
