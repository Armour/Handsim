#ifndef AMCODE_H
#define AMCODE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class AmCode : public QWidget
{
    Q_OBJECT
public:
    explicit AmCode(QWidget *parent = 0);
    QLabel *title;
    QTextEdit *text;
    QVBoxLayout *mainLayout;
signals:

public slots:

};

#endif // AMCODE_H
