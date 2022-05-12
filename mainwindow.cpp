#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"bogglewindow.h"
#include<QPalette>
#include<QPixmap>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = ui->pushButton_1->font();
    font.setPointSize(35);
    ui->pushButton_1->setFont(font);
    QFont font2 = ui->pushButton_2->font();
    font2.setPointSize(20);
    ui->pushButton_2->setFont(font2);
    ui->pushButton_1->setStyleSheet("background-color:blue;");
    ui->pushButton_2->setStyleSheet("background-color:#035397;");
    ui->pushButton_1->setStyleSheet("color:black;");
    QPixmap bkgnd("C:/Users/Montasser Brahem/OneDrive/Bureau/BOGGLEG/boo.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    sec = new BoggleWindow(this);
    sec->show();
    hide();


}
void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::about(this,"About Boggle","Boggle is a word game invented by Allan Turoff and originally distributed by Parker Brothers. The game is played using a grid of lettered dice, in which players look for words in sequences of adjacent letters.\nRules : \nEach player searches for words of two or more letters that fit the following criteria:\nWords must be at least two letters in length.\nEach letter must be a horizontal , vertical  or diagonal neighbor of the one before it.\nNo individual letter cube may be used more than once in a word.");

}

