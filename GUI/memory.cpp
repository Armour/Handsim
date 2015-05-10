#include "memory.h"
#include <QString>

Memory::Memory(QWidget *parent) : QWidget(parent) {
    QString str1;
    QByteArray ba;

    for (int i = 0; i < 32; i++) {
        str1 = QString::number(i);
        ba = str1.toLatin1();
        const char *c_str2 = ba.data();
        label[i] = new QLabel(tr(c_str2));
    }
    for (int i = 0; i < 32; i++) {
        lineEdit[i] = new QLineEdit;
        lineEdit[i]->setEnabled(false);
    }
    title = new QLabel(tr("Memory Stack"));
    title->setAlignment(Qt::AlignCenter);

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    mainLayout->addWidget(title, 0, 0, 1, 2);
    for (int i = 1; i < 33; i++) {
        mainLayout->addWidget(label[i - 1], i, 0, 1, 1);
        mainLayout->addWidget(lineEdit[i - 1], i, 1, 1, 1);
    }
}

void Memory::slotClear() {
    for (int i = 0; i < 32; i++)
        lineEdit[i]->clear();
}
