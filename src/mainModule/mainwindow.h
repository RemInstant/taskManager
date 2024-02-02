#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QListWidget>
#include "../taskModule/taskmodel.h"
#include "../taskModule/taskdelegate.h"

#include <vector>
#include <QTimer>
#include <QDebug>
#include <QCloseEvent>

#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QTranslator translator;
    QString dataDir;
    TaskModel *model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void upd();

private slots:
    // Left menu
    void onMenuTasksButtonClicked();
    void onMenuSettingsButtonClicked();
    // Tasks section
    void onTaskCreateButtonClicked();
    void onTaskChangeButtonClicked();
    void onTaskDeleteButtonClicked();
    // Settings section
    void changeLanguage(int index);

signals:

};
#endif // MAINWINDOW_H
