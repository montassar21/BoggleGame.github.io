#include"timer.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QLCDNumber>
#include<QTimer>
#include <QTime>

Timer::Timer(QWidget *parent,QString label)
    :   QWidget(parent)
{

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* headLayout = new QHBoxLayout();

    QLabel* nameLabel = new QLabel(this);
    QFont font = nameLabel->font();
    font.setPointSize(40);
    nameLabel->setFont(font);
    nameLabel->setText(label);
    headLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignLeft);
    layout->addLayout(headLayout);

    setLayout(layout);
}
