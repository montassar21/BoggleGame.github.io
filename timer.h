#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include<QLabel>
#include<QTime>
#include <QTimer>
class Timer : public QWidget
{
    Q_OBJECT
public:
    QTime *displayTime = new QTime;
     QTimer *timer = new QTimer;
    explicit Timer(QWidget *parent,QString label = "");
signals:
    void timeout();
public slots:

private:
     QString label;


};
void updateCountdown();

#endif // TIMER_H
