#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mmu.h"

extern MMU mmu;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Handsim"));

    canvas = new QWidget();
    this->setCentralWidget(canvas);

    QHBoxLayout *layout1 = new QHBoxLayout(this);

    bash = new Bash(canvas);
    mcCode = new McCode(canvas);
    memory = new Memory(canvas);
    regInfo = new RegInfo(canvas);

    QSizePolicy spBash(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spMcCode(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spMemory(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spRegInfo(QSizePolicy::Preferred, QSizePolicy::Preferred);

    spBash.setHorizontalStretch(2);
    spMcCode.setHorizontalStretch(1);
    spMemory.setHorizontalStretch(1);
    spRegInfo.setHorizontalStretch(1);

    bash->setSizePolicy(spBash);
    mcCode->setSizePolicy(spMcCode);
    memory->setSizePolicy(spMemory);
    regInfo->setSizePolicy(spRegInfo);

    createActions();
    createToolBars();

    layout1->addWidget(bash);
    layout1->addWidget(mcCode);
    layout1->addWidget(memory);
    layout1->addWidget(regInfo);

    canvas->setLayout(layout1);

    connect(bash, SIGNAL(printReg()), regInfo, SLOT(slotPrint()));
    connect(bash, SIGNAL(printReg()), memory, SLOT(slotPrint()));
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

    // connections
    connect(openFileAction, SIGNAL(triggered()), bash, SLOT(slotOpen()));
    connect(saveFileAction, SIGNAL(triggered()), bash, SLOT(slotSave()));
    connect(commitAction, SIGNAL(triggered()), bash, SLOT(slotCommit()));
    connect(clearAction, SIGNAL(triggered()), bash, SLOT(slotClear()));
    connect(clearAction, SIGNAL(triggered()), mcCode, SLOT(slotClear()));
    connect(clearAction, SIGNAL(triggered()), memory, SLOT(slotClear()));
    connect(clearAction, SIGNAL(triggered()), regInfo, SLOT(slotClear()));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(slotClear()));
}

void MainWindow::createToolBars() {
    toolBar = addToolBar("toolBar");
    toolBar->addAction(openFileAction);
    toolBar->addAction(saveFileAction);
    toolBar->addAction(commitAction);
    toolBar->addAction(clearAction);
}

void MainWindow::slotClear() {
    mmu.reset();
}
