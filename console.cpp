#include "console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

Console::Console(QWidget* parent) : QTextEdit(parent) {
    this->setStyleSheet("background-color:#9FB7B9;");
    QFont font = this->font();
    font.setPointSize(15);
    this->setFont(font);
}

void Console::clear() { this->clear(); }

void Console::write(QString msg) { this->append(msg); }

void Console::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Backspace)
        return;
    if (event->key() == Qt::Key_Delete)
        return;
    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        newLineWritten(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}
