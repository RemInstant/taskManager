#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractListModel>

#include <QList>
#include <QSize>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class TaskModel : public QAbstractListModel
{
private:
    QList<QJsonObject> dat;

public:
    explicit TaskModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void saveData(QString path);
    void loadData(QString path);
};

#endif // TASKSMODEL_H
