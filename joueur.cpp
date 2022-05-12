#include "joueur.h"
#include "wordtable.h"
#include <QHBoxLayout>
#include <QTableView>

Joueur::Joueur(QWidget* parent, QString label)
    : QWidget(parent) {
    this->setStyleSheet("background-color:#9FB7B9;");
    reset();
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* headLayout = new QHBoxLayout();

    QLabel* nameLabel = new QLabel(this);
    scoreLabel = new QLabel(this);
    QFont font = nameLabel->font();
    font.setPointSize(40);
    nameLabel->setFont(font);
    scoreLabel->setFont(font);
    nameLabel->setText(label);
    scoreLabel->setText(QString::number(score));

    headLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignLeft);
    headLayout->addWidget(scoreLabel, 0, Qt::AlignmentFlag::AlignRight);
    layout->addLayout(headLayout);

    QFrame* hline = new QFrame();
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);
    layout->addWidget(hline);

    wordTable = new WordTable();
    layout->addWidget(wordTable);

    setLayout(layout);
}

void Joueur::addScore(int score) {
    this->score += score;
    scoreLabel->setText(QString::number(this->score));
}

void Joueur::addWord(QString word) {
    this->words.append(word);
    this->wordTable->addWord(word);
}

bool Joueur::checkWord(QString word) {
    return this->words.contains(word);
}

void Joueur::reset() {
    this->score = 0;
    this->words.clear();
    if (this->wordTable)
        this->wordTable->reset();
    if (scoreLabel)
        scoreLabel->setText(QString::number(this->score));
}
