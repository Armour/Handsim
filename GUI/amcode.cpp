#include "amcode.h"
#include <QTextEdit>
#include <QVBoxLayout>

AmCode::AmCode(QWidget *parent) : QWidget(parent) {
    title = new QLabel(tr("Armour Code"));
    title->setAlignment(Qt::AlignCenter);
    text = new QTextEdit;
    text->setEnabled(false);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title);
    mainLayout->addWidget(text);
}
