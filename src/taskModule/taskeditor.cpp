#include "taskeditor.h"
#include "ui_taskeditor.h"

TaskEditor::TaskEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskEditor)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
}

TaskEditor::~TaskEditor()
{
    delete ui;
}

void TaskEditor::setData(QJsonObject val)
{
    data = val;
    ui->plainTextEdit->setPlainText(val.value("desc").toString());
}

QJsonObject TaskEditor::getData() const
{
    return data;
}

void TaskEditor::onOkButtonClicked()
{
    data.insert("desc", ui->plainTextEdit->toPlainText());
    data.insert("show", true);
    this->close();
}


void TaskEditor::onCancelButtonClicked()
{
    // NO OTHER CODE HERE!
    this->close();
}

