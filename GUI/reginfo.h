#ifndef REGINFO_H
#define REGINFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

class RegInfo : public QWidget
{
    Q_OBJECT
public:
    explicit RegInfo(QWidget *parent = 0);

    QLabel *title;
    QLabel *zrLabel, *atLabel, *v0Label, *v1Label, *a0Label, *a1Label, *a2Label, *a3Label,
           *t0Label, *t1Label, *t2Label, *t3Label, *t4Label, *t5Label, *t6Label, *t7Label,
           *s0Label, *s1Label, *s2Label, *s3Label, *s4Label, *s5Label, *s6Label, *s7Label,
           *t8Label, *t9Label, *k0Label, *k1Label, *gpLabel, *spLabel, *fpLabel, *raLabel;
    QLineEdit *zrLineEdit, *atLineEdit, *v0LineEdit, *v1LineEdit, *a0LineEdit, *a1LineEdit, *a2LineEdit, *a3LineEdit,
              *t0LineEdit, *t1LineEdit, *t2LineEdit, *t3LineEdit, *t4LineEdit, *t5LineEdit, *t6LineEdit, *t7LineEdit,
              *s0LineEdit, *s1LineEdit, *s2LineEdit, *s3LineEdit, *s4LineEdit, *s5LineEdit, *s6LineEdit, *s7LineEdit,
              *t8LineEdit, *t9LineEdit, *k0LineEdit, *k1LineEdit, *gpLineEdit, *spLineEdit, *fpLineEdit, *raLineEdit;
    QGridLayout *mainLayout;
signals:

public slots:
    void slotClear();
    void slotPrint();
};

#endif // REGINFO_H
