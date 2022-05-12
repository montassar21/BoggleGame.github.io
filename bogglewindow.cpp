#include "bogglewindow.h"
#include "ui_bogglewindow.h"
#include "joueur.h"
#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include<QMessageBox>

BoggleWindow::BoggleWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoggleWindow)
{
      ui->setupUi(this);
      this->setWindowTitle("Boggle!");
      this->setWindowState(Qt::WindowMaximized);
      this->setStyleSheet("background-color:#4B7BE5;");
      me = new Joueur(this, "Player 1");
      player = new Joueur(this, "Player 2");
      board = new Board(this);
      console = new Console(this);
      me->setGeometry(20, 20, 330, 350);
      player->setGeometry(20, 380, 330, 350);
      board->setGeometry(440, 100, 620, 620);
      console->setGeometry(1150,40, 330, 680);
      QFont font = ui->timerLabel->font();
      font.setPointSize(40);
      ui->timerLabel->setFont(font);
      QFile qFile("C:/Users/Montasser Brahem/OneDrive/Bureau/BOGGLEG/EnglishWords.txt");
      if (!qFile.open(QIODevice::ReadOnly)) {
          throw new std::runtime_error("Resource file not found!");
      }
      lex = new Lexicon(qFile);
      *displayTime = ui->timeEdit->time();
      ui->timerLabel->setText(displayTime->toString("mm:ss"));


      console->write(
          "Welcome to the game Boggle!\nPress Enter keyboard to start a game or to restart the game:\n");
      QObject::connect(console, &Console::newLineWritten, this,
                       &BoggleWindow::command);
      connect(timer,SIGNAL(timeout()), this, SLOT(updateTime()));
      timer->setSingleShot(true);

}

BoggleWindow::~BoggleWindow()
{
    delete ui;
}
void BoggleWindow::command(QString cmd) {
    if (start == 0) {
        me->reset();
        player->reset();
        board->allres.clear();
        board->shake();
        start = 1;
        clear();
        console->write(
            "Welcome to the game Boggle!\nPress Enter keyboard to start a new game:");
        QTime newTime = displayTime->addSecs(nb);
        displayTime->setHMS(newTime.hour(),newTime.minute(),newTime.second());
        ui->timerLabel->setText(displayTime->toString("mm:ss"));
        nb=0;
        return;
    }
    if (start == 1) {
        if (cmd.isEmpty()) {
            start = 2;
            console->write("[*_*] Game start!");
            console->write("Tentative du player 1 :");
            on_startButton_clicked();
            timer->start();

        } else {
            if (!board->input(cmd)) {
                console->write("[-_-] Letter too short! Try another:");
            } else {
                start = 2;
                console->write("[*_*] Game start!");
                on_startButton_clicked();
                timer->start();
            }
        }
        return;
    }
if(count %2==0){
    if (cmd.isEmpty()) {
        int score = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                score += board->findAll(lex, "", i, j);
        board->highlight(true);
        for (auto &i : board->allres)
            if (me->checkWord(i)){
                score -= i.length();

}
            else{
        start = 0;
            }
        console->write("[*_*] Press any key to start next game!");
        timer->stop();
        score1=0;
        score2=0;
        return;
    }

    cmd = cmd.toLower();
    if (cmd.size() < 2) {
        console->write("[-_-] Word too short!");
        count++;
        console->write("Tentative du player 2 :");



        return;
    }
    if (me->checkWord(cmd) ||player->checkWord(cmd)) {
        console->write("[-_-] Already exist!");
        count++;
        console->write("Tentative du player 2 :");



        return;
    }
    if (!lex->contains(cmd.toStdString())) {
        console->write("[-_-] Invalid word!");
        count++;
        console->write("Tentative du player 2 :");

        return;
    }

    QString tmp = cmd.toUpper();
    bool flag = false;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            if (board->checkWord(tmp, i, j) && !player->checkWord(cmd)) {
                board->highlight();
                me->addWord(cmd);
                me->addScore(cmd.length());
                score1+=cmd.length();
                console->write("[^_^] Correct!");
                flag = true;
                break;
            }
        if (flag)
            break;
    }

    if (!flag){
        console->write("[-_-] Word is not in board!");
        count++;
        console->write("Tentative du player 2 :");
        return;

    }

}
else {
    if (cmd.isEmpty()) {
        int score = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                score += board->findAll(lex, "", i, j);
        board->highlight(true);
        for (auto i : board->allres)
            if (player->checkWord(i)){
                score -= i.length() ;
    }
            else
        start = 0;
        console->write("[*_*] Press any key to start next game!");
        timer->stop();
        score1=0;
        score2=0;
        return;
    }

    cmd = cmd.toLower();
    if (cmd.size() < 2) {
        console->write("[-_-] Word too short!");
        count++;
        console->write("Tentative du player 1 :");


        return;
    }
    if (player->checkWord(cmd) ||me->checkWord(cmd)) {
        console->write("[-_-] Already exist!");
        count++;
        console->write("Tentative du player 1 :");

        return;
    }
    if (!lex->contains(cmd.toStdString())) {
        console->write("[-_-] Invalid word!");
        count++;
        console->write("Tentative du player 1 :");

        return;
    }

    QString tmp = cmd.toUpper();
    bool flag = false;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            if (board->checkWord(tmp, i, j) && !me->checkWord(cmd)) {
                board->highlight();
                player->addWord(cmd);
                player->addScore(cmd.length());
                score2+=cmd.length();
                console->write("[^_^] Correct!");

                flag = true;
                break;
            }
        if (flag)
            break;
    }
    if (!flag){
        console->write("[-_-] Word is not in board!");
        count++;
        console->write("Tentative du player 1 :");
        return;


    }
}
if(count%2==0)
    console->write("Tentative du player 2 :");
  else         console->write("Tentative du player 1 :");

count++;
}
void BoggleWindow::click(int posi, int posj, QString l,Cube *c) {
    if(count %2 ==0){
    if (start == 2) {
        if ((lasti == -1 && lastj == -1) ||
            (qAbs(posi - lasti) <= 1 && qAbs(posj - lastj) <= 1)) {
            if (!vis[posi][posj]) {
                if (lex->containsPrefix(
                        (laststr + l.toLower()).toStdString())) {
                    laststr.append(l.toLower());
                    if (lex->contains(laststr.toStdString()) &&
                        !me->checkWord(laststr) && laststr.size() >= 2 && !player->checkWord(laststr)) {
                        me->addWord(laststr);
                        me->addScore(laststr.length());
                        score1+=laststr.length();
                        console->write(laststr);
                        console->write("[^_^] Correct!");
                        console->write("Tentative du player 2 : \n");
                        count++;

                        clear();
                        return;
                    }
                    if (lasti == -1 && lastj == -1)
                        board->highlight(true);
                         c->highlight(255 - rand() % 255);
                    lasti = posi;
                    lastj = posj;
                    vis[posi][posj] = 1;
                } else {
                    clear();
                    console->write("[-_-] Invalid word!");
                    console->write("Tentative du player 2 : \n");
                    count++;


                }
            }
        }
    }
   }
    else {
        if (start == 2) {
            if ((lasti == -1 && lastj == -1) ||
                (qAbs(posi - lasti) <= 1 && qAbs(posj - lastj) <= 1)) {
                if (!vis[posi][posj]) {
                    if (lex->containsPrefix(
                            (laststr + l.toLower()).toStdString())) {
                        laststr.append(l.toLower());
                        if (lex->contains(laststr.toStdString()) &&
                            !me->checkWord(laststr) && laststr.size() >= 2 && !player->checkWord(laststr)) {
                            player->addWord(laststr);
                            player->addScore(laststr.length());
                            score2+=laststr.length();
                            console->write(laststr);
                            console->write("[^_^] Correct!");
                            console->write("Tentative du player 1 : \n");
                            count++;

                            clear();
                            return;
                        }
                        if (lasti == -1 && lastj == -1)
                            board->highlight(true);
                             c->highlight(255 - rand() % 255);
                        lasti = posi;
                        lastj = posj;
                        vis[posi][posj] = 1;
                    } else {
                        clear();
                        console->write("[-_-] Invalid word!");
                        console->write("Tentative du player 1 : \n");
                        count++;


                    }
                }
            }
        }

    }
}

void BoggleWindow::clear() {
    lasti = lastj = -1;
    memset(vis, 0, sizeof(vis));
    laststr.clear();
    board->highlight(true);


}
void BoggleWindow::on_startButton_clicked()
{
    if(buttonStart == true)
    {
        buttonStart = false;
        ui->startButton->setText("Stop");
        ui->timeEdit->setEnabled(false);
        *displayTime = ui->timeEdit->time();
        ui->timerLabel->setText(displayTime->toString("mm:ss"));
        timer->start(1000);
    }
    else
    {
        buttonStart = true;
        ui->startButton->setText("Start");
        ui->timeEdit->setEnabled(true);
        ui->timeEdit->setTime(*displayTime);
        timer->stop();
    }
}

void BoggleWindow::updateTime()
{
    QTime newTime = displayTime->addSecs(-1);
    displayTime->setHMS(newTime.hour(),newTime.minute(),newTime.second());
    ui->timerLabel->setText(displayTime->toString("mm:ss"));
    if(displayTime->hour() != 0 ||
            displayTime->minute() != 0 ||
            displayTime->second() != 0)
    {
        timer->start(1000);
        nb++;
    }
    else
    {
        buttonStart = true;
        ui->startButton->setText("Start");
        timer->stop();
        console->write("Game Over ! .[*_*] Press Enter key to start next game!\n");
        if(score1>score2){
        QMessageBox::about(this,"Game Over !","Player 1 win the Game");}
        else if(score2>score1){
            QMessageBox::about(this,"Game Over !","Player  2 win the Game");}

      else{
          QMessageBox::about(this,"Game Over !","No one Win the Game");}



}




    }

