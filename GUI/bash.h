#ifndef BASH_H
#define BASH_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class Bash : public QWidget
{
    Q_OBJECT
public:
    explicit Bash(QWidget *parent = 0);
    QLabel *title;
    QTextEdit *text;
    QVBoxLayout *mainLayout;
signals:

public slots:

};

#endif // BASH_H
