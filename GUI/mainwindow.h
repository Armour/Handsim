#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QToolButton>
#include <QTextCharFormat>
#include <QHBoxLayout>
#include <QGridLayout>
#include "bash.h"
#include "mccode.h"
#include "memory.h"
#include "reginfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createToolBars();

    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QString fileName;

    QWidget *canvas;
    Bash *bash;
    McCode *mcCode;
    Memory *memory;

    RegInfo *regInfo;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *commitAction;
    QAction *clearAction;
    QToolBar *toolBar;
public slots:
    void slotClear();
};

#endif // MAINWINDOW_H
