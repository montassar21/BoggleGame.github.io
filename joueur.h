#ifndef JOUEUR_H
#define JOUEUR_H
#include "wordtable.h"
#include <QWidget>
#include <QLabel>
class Joueur : public QWidget {
    Q_OBJECT
public:
    explicit Joueur(QWidget* parent, QString label = "");
    void addScore(int s);
    void addWord(QString word);
    bool checkWord(QString word);
    void reset();
private:
    QString label;
    QList<QString> words;
    QLabel* scoreLabel = nullptr;
    int score;
    WordTable* wordTable = nullptr;
};
#endif  // JOUEUR_H
