#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Handsim"));

    createActions();
    createToolBars();

    canvas = new QWidget();
    this->setCentralWidget(canvas);

    QHBoxLayout *layout1 = new QHBoxLayout(this);

    bash = new Bash(canvas);
    regInfo = new RegInfo(canvas);

    QSizePolicy spBash(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spRegInfo(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spBash.setHorizontalStretch(1);
    spRegInfo.setHorizontalStretch(1);
    bash->setSizePolicy(spBash);
    regInfo->setSizePolicy(spRegInfo);

    layout1->addWidget(bash);
    layout1->addWidget(regInfo);
    layout1->addWidget(mcCode);

    canvas->setLayout(layout1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions() {
    // 'open file' action
    openFileAction = new QAction(QIcon("open.png"), tr("open"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("open a file"));

    // 'save file' action
    saveFileAction = new QAction(QIcon("save.png"), tr("save"), this);
    saveFileAction->setShortcut(tr("Ctrl+S"));
    openFileAction->setStatusTip(tr("save commands into file"));

    // commit commands action
    commitAction = new QAction(QIcon("commit.png"), tr("commit"), this);
    saveFileAction->setShortcut(tr("Ctrl+R"));
    openFileAction->setStatusTip(tr("commit the commands"));

    // clear bash and registers action
    clearAction = new QAction(QIcon("clear.png"), tr("clear"), this);
    saveFileAction->setShortcut(tr("Ctrl+C"));
    openFileAction->setStatusTip(tr("clear records"));
}

void MainWindow::createToolBars() {
    toolBar = addToolBar("toolBar");
    toolBar->addAction(openFileAction);
    toolBar->addAction(saveFileAction);
    toolBar->addAction(commitAction);
    toolBar->addAction(clearAction);
}
