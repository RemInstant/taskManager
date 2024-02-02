#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Left menu
    connect(ui->menuTasksButton, SIGNAL(clicked()), this, SLOT(onMenuTasksButtonClicked()));
    connect(ui->menuSettingsButton, SIGNAL(clicked()), this, SLOT(onMenuSettingsButtonClicked()));

    // Task section
    QListView *tasksView = ui->tasksView;
    model = new TaskModel(this);
    TaskDelegate* del = new TaskDelegate(this);

    tasksView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(tasksView, SIGNAL(clicked(QModelIndex)), del, SLOT(onTaskClicked(QModelIndex)));
    connect(tasksView, SIGNAL(doubleClicked(QModelIndex)), del, SLOT(onTaskDoubleClicked(QModelIndex)));
    connect(ui->taskCreateButton, SIGNAL(clicked()), this, SLOT(onTaskCreateButtonClicked()));
    connect(ui->taskChangeButton, SIGNAL(clicked()), this, SLOT(onTaskChangeButtonClicked()));
    connect(ui->taskDeleteButton, SIGNAL(clicked()), this, SLOT(onTaskDeleteButtonClicked()));

    tasksView->setItemDelegate(del);
    tasksView->setModel(model);

    dataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0);
    if(!QDir(dataDir).exists())
        QDir().mkdir(dataDir);

    model->loadData(dataDir);

    // Settings section
    connect(ui->languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //model->dumpObjectInfo()
    model->saveData(dataDir);
    event->accept();
}

void MainWindow::upd()
{
    qDebug() << "UPD";
    ui->tasksView->update();
}

void MainWindow::onMenuTasksButtonClicked()
{
    ui->sections->setCurrentWidget(ui->tasksSection);
}

void MainWindow::onMenuSettingsButtonClicked()
{
    ui->sections->setCurrentWidget(ui->settingsSection);
}

void MainWindow::onTaskCreateButtonClicked()
{
    QItemSelectionModel *selModel = ui->tasksView->selectionModel();
    QModelIndex index = selModel->currentIndex();

    int pos = ui->tasksView->model()->rowCount();

    if(index.isValid())
        pos = index.row()+1;


    ui->tasksView->model()->insertRow(pos);

    QModelIndex newIndex = ui->tasksView->model()->index(pos, 0);

    ui->tasksView->edit(newIndex);

    TaskDelegate *del = static_cast<TaskDelegate*>(ui->tasksView->itemDelegate());
    del->setLastClicked(newIndex, false);

    selModel->clear();
    selModel->setCurrentIndex(newIndex, QItemSelectionModel::Select);
}

void MainWindow::onTaskChangeButtonClicked()
{
    QItemSelectionModel *selModel = ui->tasksView->selectionModel();
    QModelIndex index = selModel->currentIndex();

    if(index.isValid())
        ui->tasksView->edit(index);
}

void MainWindow::onTaskDeleteButtonClicked()
{
    QItemSelectionModel *selModel = ui->tasksView->selectionModel();
    QModelIndex index = selModel->currentIndex();

    if(index.isValid())
    {
        ui->tasksView->model()->removeRow(index.row(), index);
        QModelIndex nextIndex = ui->tasksView->model()->index(index.row(), 0);
        selModel->setCurrentIndex(nextIndex, QItemSelectionModel::Select);
    }
}

void MainWindow::changeLanguage(int index)
{
    bool langLoadFlag = true;
    bool langInstallFlag = true;
    bool t1 = translator.load(":/taskManager_ru_RU.qm");
    switch (index)
    {
    case 0:
        langLoadFlag = translator.load(":/taskManager_ru_RU.qm");
        break;
    case 1:
        langLoadFlag = translator.load(":/taskManager_en_US.qm");
        break;
    default:
        qDebug() << "Language change error: unexpected index";
        break;
    }
    if (!langLoadFlag)
    {
        qDebug() << "Language change error: cannot load language";
        return;
    }
    langInstallFlag = qApp->installTranslator(&translator);
    if (!langInstallFlag)
    {
        qDebug() << "Language change error: cannot install translator";
        return;
    }
    ui->retranslateUi(this);
}
