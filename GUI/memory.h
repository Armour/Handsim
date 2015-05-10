#ifndef MEMORY_H
#define MEMORY_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

class Memory : public QWidget
{
    Q_OBJECT
public:
    explicit Memory(QWidget *parent = 0);
    QLabel *title;
    QLabel *label[32];
    QLineEdit *lineEdit[32];
    QGridLayout *mainLayout;
signals:

public slots:
    void slotClear();
};

#endif // MEMORY_H
