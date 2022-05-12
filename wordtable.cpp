#include "wordtable.h"
#include <QHeaderView>
#include <QScrollBar>

WordTable::WordTable(QWidget* parent, int maxCol) : QTableWidget(parent) {
    this->maxCol = maxCol;
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setShowGrid(false);
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    this->horizontalScrollBar()->hide();
    this->verticalScrollBar()->hide();
    QFont font = this->font();
    font.setPointSize(25);
    this->setFont(font);
    this->setStyleSheet("color:black;");

}

void WordTable::addWord(QString word) {
    if (col == maxCol) {
        row++;
        this->model()->insertRow(row);
        col = 0;
    }
    this->setItem(row, col, new QTableWidgetItem(word));
    col++;
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
}

void WordTable::reset() {
    row = 0;
    col = 0;
    this->setColumnCount(maxCol);
    this->setRowCount(0);
    this->setRowCount(1);
}
