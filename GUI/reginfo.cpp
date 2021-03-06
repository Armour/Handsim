#include "reginfo.h"
#include "mmu.h"

extern MMU mmu;

char *word2char(unsigned int value) {
    char *c;
    c = new char[33];
    for (int i = 0; i < 32; i++) {
        c[31 - i] = ((value & (1 << i)) == 0) ? '0' : '1';
    }
    c[32] = '\0';
    return c;
}

RegInfo::RegInfo(QWidget *parent) :
    QWidget(parent)
{
    zrLabel = new QLabel(tr("$zero"));
    atLabel = new QLabel(tr("$at"));
    v0Label = new QLabel(tr("$v0"));
    v1Label = new QLabel(tr("$v1"));
    a0Label = new QLabel(tr("$a0"));
    a1Label = new QLabel(tr("$a1"));
    a2Label = new QLabel(tr("$a2"));
    a3Label = new QLabel(tr("$a3"));
    t0Label = new QLabel(tr("$t0"));
    t1Label = new QLabel(tr("$t1"));
    t2Label = new QLabel(tr("$t2"));
    t3Label = new QLabel(tr("$t3"));
    t4Label = new QLabel(tr("$t4"));
    t5Label = new QLabel(tr("$t5"));
    t6Label = new QLabel(tr("$t6"));
    t7Label = new QLabel(tr("$t7"));
    s0Label = new QLabel(tr("$s0"));
    s1Label = new QLabel(tr("$s1"));
    s2Label = new QLabel(tr("$s2"));
    s3Label = new QLabel(tr("$s3"));
    s4Label = new QLabel(tr("$s4"));
    s5Label = new QLabel(tr("$s5"));
    s6Label = new QLabel(tr("$s6"));
    s7Label = new QLabel(tr("$s7"));
    t8Label = new QLabel(tr("$t8"));
    t9Label = new QLabel(tr("$t9"));
    k0Label = new QLabel(tr("$k0"));
    k1Label = new QLabel(tr("$k1"));
    gpLabel = new QLabel(tr("$gp"));
    spLabel = new QLabel(tr("$sp"));
    fpLabel = new QLabel(tr("$fp"));
    raLabel = new QLabel(tr("$ra"));

    zrLineEdit = new QLineEdit;
    atLineEdit = new QLineEdit;
    v0LineEdit = new QLineEdit;
    v1LineEdit = new QLineEdit;
    a0LineEdit = new QLineEdit;
    a1LineEdit = new QLineEdit;
    a2LineEdit = new QLineEdit;
    a3LineEdit = new QLineEdit;
    t0LineEdit = new QLineEdit;
    t1LineEdit = new QLineEdit;
    t2LineEdit = new QLineEdit;
    t3LineEdit = new QLineEdit;
    t4LineEdit = new QLineEdit;
    t5LineEdit = new QLineEdit;
    t6LineEdit = new QLineEdit;
    t7LineEdit = new QLineEdit;
    s0LineEdit = new QLineEdit;
    s1LineEdit = new QLineEdit;
    s2LineEdit = new QLineEdit;
    s3LineEdit = new QLineEdit;
    s4LineEdit = new QLineEdit;
    s5LineEdit = new QLineEdit;
    s6LineEdit = new QLineEdit;
    s7LineEdit = new QLineEdit;
    t8LineEdit = new QLineEdit;
    t9LineEdit = new QLineEdit;
    k0LineEdit = new QLineEdit;
    k1LineEdit = new QLineEdit;
    gpLineEdit = new QLineEdit;
    spLineEdit = new QLineEdit;
    fpLineEdit = new QLineEdit;
    raLineEdit = new QLineEdit;

    zrLineEdit->setEnabled(false);
    atLineEdit->setEnabled(false);
    v0LineEdit->setEnabled(false);
    v1LineEdit->setEnabled(false);
    a0LineEdit->setEnabled(false);
    a1LineEdit->setEnabled(false);
    a2LineEdit->setEnabled(false);
    a3LineEdit->setEnabled(false);
    t0LineEdit->setEnabled(false);
    t1LineEdit->setEnabled(false);
    t2LineEdit->setEnabled(false);
    t3LineEdit->setEnabled(false);
    t4LineEdit->setEnabled(false);
    t5LineEdit->setEnabled(false);
    t6LineEdit->setEnabled(false);
    t7LineEdit->setEnabled(false);
    s0LineEdit->setEnabled(false);
    s1LineEdit->setEnabled(false);
    s2LineEdit->setEnabled(false);
    s3LineEdit->setEnabled(false);
    s4LineEdit->setEnabled(false);
    s5LineEdit->setEnabled(false);
    s6LineEdit->setEnabled(false);
    s7LineEdit->setEnabled(false);
    t8LineEdit->setEnabled(false);
    t9LineEdit->setEnabled(false);
    k0LineEdit->setEnabled(false);
    k1LineEdit->setEnabled(false);
    gpLineEdit->setEnabled(false);
    spLineEdit->setEnabled(false);
    fpLineEdit->setEnabled(false);
    raLineEdit->setEnabled(false);

    title = new QLabel(tr("Source Code"));
    title->setAlignment(Qt::AlignCenter);

    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    mainLayout->addWidget(title, 0, 0, 1, 2);

    mainLayout->addWidget(zrLabel, 1, 0, 1, 1);
    mainLayout->addWidget(zrLineEdit, 1, 1, 1, 1);
    mainLayout->addWidget(atLabel, 2, 0, 1, 1);
    mainLayout->addWidget(atLineEdit, 2, 1, 1, 1);
    mainLayout->addWidget(v0Label, 3, 0, 1, 1);
    mainLayout->addWidget(v0LineEdit, 3, 1, 1, 1);
    mainLayout->addWidget(v1Label, 4, 0, 1, 1);
    mainLayout->addWidget(v1LineEdit, 4, 1, 1, 1);
    mainLayout->addWidget(a0Label, 5, 0, 1, 1);
    mainLayout->addWidget(a0LineEdit, 5, 1, 1, 1);
    mainLayout->addWidget(a1Label, 6, 0, 1, 1);
    mainLayout->addWidget(a1LineEdit, 6, 1, 1, 1);
    mainLayout->addWidget(a2Label, 7, 0, 1, 1);
    mainLayout->addWidget(a2LineEdit, 7, 1, 1, 1);
    mainLayout->addWidget(a3Label, 8, 0, 1, 1);
    mainLayout->addWidget(a3LineEdit, 8, 1, 1, 1);
    mainLayout->addWidget(t0Label, 9, 0, 1, 1);
    mainLayout->addWidget(t0LineEdit, 9, 1, 1, 1);
    mainLayout->addWidget(t1Label, 10, 0, 1, 1);
    mainLayout->addWidget(t1LineEdit, 10, 1, 1, 1);
    mainLayout->addWidget(t2Label, 11, 0, 1, 1);
    mainLayout->addWidget(t2LineEdit, 11, 1, 1, 1);
    mainLayout->addWidget(t3Label, 12, 0, 1, 1);
    mainLayout->addWidget(t3LineEdit, 12, 1, 1, 1);
    mainLayout->addWidget(t4Label, 13, 0, 1, 1);
    mainLayout->addWidget(t4LineEdit, 13, 1, 1, 1);
    mainLayout->addWidget(t5Label, 14, 0, 1, 1);
    mainLayout->addWidget(t5LineEdit, 14, 1, 1, 1);
    mainLayout->addWidget(t6Label, 15, 0, 1, 1);
    mainLayout->addWidget(t6LineEdit, 15, 1, 1, 1);
    mainLayout->addWidget(t7Label, 16, 0, 1, 1);
    mainLayout->addWidget(t7LineEdit, 16, 1, 1, 1);
    mainLayout->addWidget(s0Label, 17, 0, 1, 1);
    mainLayout->addWidget(s0LineEdit, 17, 1, 1, 1);
    mainLayout->addWidget(s1Label, 18, 0, 1, 1);
    mainLayout->addWidget(s1LineEdit, 18, 1, 1, 1);
    mainLayout->addWidget(s2Label, 19, 0, 1, 1);
    mainLayout->addWidget(s2LineEdit, 19, 1, 1, 1);
    mainLayout->addWidget(s3Label, 20, 0, 1, 1);
    mainLayout->addWidget(s3LineEdit, 20, 1, 1, 1);
    mainLayout->addWidget(s4Label, 21, 0, 1, 1);
    mainLayout->addWidget(s4LineEdit, 21, 1, 1, 1);
    mainLayout->addWidget(s5Label, 22, 0, 1, 1);
    mainLayout->addWidget(s5LineEdit, 22, 1, 1, 1);
    mainLayout->addWidget(s6Label, 23, 0, 1, 1);
    mainLayout->addWidget(s6LineEdit, 23, 1, 1, 1);
    mainLayout->addWidget(s7Label, 24, 0, 1, 1);
    mainLayout->addWidget(s7LineEdit, 24, 1, 1, 1);
    mainLayout->addWidget(t8Label, 25, 0, 1, 1);
    mainLayout->addWidget(t8LineEdit, 25, 1, 1, 1);
    mainLayout->addWidget(t9Label, 26, 0, 1, 1);
    mainLayout->addWidget(t9LineEdit, 26, 1, 1, 1);
    mainLayout->addWidget(k0Label, 27, 0, 1, 1);
    mainLayout->addWidget(k0LineEdit, 27, 1, 1, 1);
    mainLayout->addWidget(k1Label, 28, 0, 1, 1);
    mainLayout->addWidget(k1LineEdit, 28, 1, 1, 1);
    mainLayout->addWidget(gpLabel, 29, 0, 1, 1);
    mainLayout->addWidget(gpLineEdit, 29, 1, 1, 1);
    mainLayout->addWidget(spLabel, 30, 0, 1, 1);
    mainLayout->addWidget(spLineEdit, 30, 1, 1, 1);
    mainLayout->addWidget(fpLabel, 31, 0, 1, 1);
    mainLayout->addWidget(fpLineEdit, 31, 1, 1, 1);
    mainLayout->addWidget(raLabel, 32, 0, 1, 1);
    mainLayout->addWidget(raLineEdit, 32, 1, 1, 1);

}

void RegInfo::slotClear() {
    zrLineEdit->clear();
    atLineEdit->clear();
    v0LineEdit->clear();
    v1LineEdit->clear();
    a0LineEdit->clear();
    a1LineEdit->clear();
    a2LineEdit->clear();
    a3LineEdit->clear();
    t0LineEdit->clear();
    t1LineEdit->clear();
    t2LineEdit->clear();
    t3LineEdit->clear();
    t4LineEdit->clear();
    t5LineEdit->clear();
    t6LineEdit->clear();
    t7LineEdit->clear();
    s0LineEdit->clear();
    s1LineEdit->clear();
    s2LineEdit->clear();
    s3LineEdit->clear();
    s4LineEdit->clear();
    s5LineEdit->clear();
    s6LineEdit->clear();
    s7LineEdit->clear();
    t8LineEdit->clear();
    t9LineEdit->clear();
    k0LineEdit->clear();
    k1LineEdit->clear();
    gpLineEdit->clear();
    spLineEdit->clear();
    fpLineEdit->clear();
    raLineEdit->clear();
}

void RegInfo::slotPrint() {
    zrLineEdit->setText(word2char(mmu.getReg(0)));
    atLineEdit->setText(word2char(mmu.getReg(1)));
    v0LineEdit->setText(word2char(mmu.getReg(2)));
    v1LineEdit->setText(word2char(mmu.getReg(3)));
    a0LineEdit->setText(word2char(mmu.getReg(4)));
    a1LineEdit->setText(word2char(mmu.getReg(5)));
    a2LineEdit->setText(word2char(mmu.getReg(6)));
    a3LineEdit->setText(word2char(mmu.getReg(7)));
    t0LineEdit->setText(word2char(mmu.getReg(8)));
    t1LineEdit->setText(word2char(mmu.getReg(9)));
    t2LineEdit->setText(word2char(mmu.getReg(10)));
    t3LineEdit->setText(word2char(mmu.getReg(11)));
    t4LineEdit->setText(word2char(mmu.getReg(12)));
    t5LineEdit->setText(word2char(mmu.getReg(13)));
    t6LineEdit->setText(word2char(mmu.getReg(14)));
    t7LineEdit->setText(word2char(mmu.getReg(15)));
    s0LineEdit->setText(word2char(mmu.getReg(16)));
    s1LineEdit->setText(word2char(mmu.getReg(17)));
    s2LineEdit->setText(word2char(mmu.getReg(18)));
    s3LineEdit->setText(word2char(mmu.getReg(19)));
    s4LineEdit->setText(word2char(mmu.getReg(20)));
    s5LineEdit->setText(word2char(mmu.getReg(21)));
    s6LineEdit->setText(word2char(mmu.getReg(22)));
    s7LineEdit->setText(word2char(mmu.getReg(23)));
    t8LineEdit->setText(word2char(mmu.getReg(24)));
    t9LineEdit->setText(word2char(mmu.getReg(25)));
    k0LineEdit->setText(word2char(mmu.getReg(26)));
    k1LineEdit->setText(word2char(mmu.getReg(27)));
    gpLineEdit->setText(word2char(mmu.getReg(28)));
    spLineEdit->setText(word2char(mmu.getReg(29)));
    fpLineEdit->setText(word2char(mmu.getReg(30)));
    raLineEdit->setText(word2char(mmu.getReg(31)));

}
