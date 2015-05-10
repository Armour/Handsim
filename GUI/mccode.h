#ifndef MCCODE_H
#define MCCODE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class McCode : public QWidget
{
    Q_OBJECT
public:
    explicit McCode(QWidget *parent = 0);
    QLabel *title;
    QTextEdit *text;
    QVBoxLayout *mainLayout;
signals:

public slots:
    void slotClear();
};

#endif // MCCODE_H
