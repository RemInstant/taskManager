#ifndef TASKEDITOR_H
#define TASKEDITOR_H

#include <QDialog>
#include <QJsonObject>

#include <QMessageBox>

namespace Ui {
class TaskEditor;
}

class TaskEditor : public QDialog
{
    Q_OBJECT
private:
    Ui::TaskEditor *ui;
    QJsonObject data;

public:
    explicit TaskEditor(QWidget *parent = nullptr);
    ~TaskEditor();

    void setData(QJsonObject val);
    QJsonObject getData() const;

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();
};

#endif // TASKEDITOR_H
