#include "bash.h"
#include <QTextEdit>
#include <QVBoxLayout>

Bash::Bash(QWidget *parent) : QWidget(parent) {
    title = new QLabel(tr("Source Code"));
    title->setAlignment(Qt::AlignCenter);
    text = new QTextEdit;
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title);
    mainLayout->addWidget(text);
}
