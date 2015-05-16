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
    void runMMU();
public slots:
    void slotOpen();
    void slotSave();
    void slotCommit();
    void slotClear();
};

#endif // BASH_H
