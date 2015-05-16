#include "mccode.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
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

void McCode::slotPrint() {
    QFile file("ASM/machineCode.mips");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    QString machineCode = in.readAll();
    text->clear();
    text->insertPlainText(machineCode);
}
