#ifndef CUBE_H
#define CUBE_H
#include <QLabel>
#include <QWidget>
class Cube : public QWidget {
    Q_OBJECT
public:
    explicit Cube(QWidget* parent);
    void setLetter(QString l);
    void highlight(int degree);
    void mousePressEvent(QMouseEvent* event);
    void setPos(int i, int j);
signals:
    void selected(int i, int j, QString l, Cube* c);
private:
    int posi;
    int posj;
    QLabel* label;
};

#endif  // CUBE_H
