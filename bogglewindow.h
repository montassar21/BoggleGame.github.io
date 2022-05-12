#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H
#include "board.h"
#include "console.h"
#include "joueur.h"
#include "lexicon.h"
#include <QDialog>
#include <QTime>
#include <QTimer>
namespace Ui {
class BoggleWindow;
}

class BoggleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BoggleWindow(QWidget *parent = nullptr);
    ~BoggleWindow();
    QTime *displayTime = new QTime;
    QTimer *timer = new QTimer;
    bool buttonStart = true;
public slots:
    void command(QString cmd);
    void click(int posi, int posj, QString l, Cube* c);
    void updateTime();
private slots:
    void on_startButton_clicked();

private:
    void clear();
    int start = 1;
    Joueur* me;
    Joueur *player;
    Board* board;
    Console* console;
    Lexicon* lex;
    int lasti = -1;
    int lastj = -1;
    bool vis[5][5] = {{0}};
    int lasti1 = -1;
    int lastj1 = -1;
    bool vis1[5][5] = {{0}};
    QString laststr;
    int nb=0;
int count=0;

    static const int BOGGLE_WINDOW_WIDTH = 450;
    static const int BOGGLE_WINDOW_HEIGHT = 600;

private:
    Ui::BoggleWindow *ui;
    int score1=0;
    int score2=0;
};

#endif // BOGGLEWINDOW_H
