#include "mccode.h"
#include <QTextEdit>
#include <QVBoxLayout>

McCode::McCode(QWidget *parent) : QWidget(parent) {
    title = new QLabel(tr("Machine Code"));
    title->setAlignment(Qt::AlignCenter);
    text = new QTextEdit;
    text->setEnabled(false);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title);
    mainLayout->addWidget(text);
}

void McCode::slotClear() {
    text->clear();
}
