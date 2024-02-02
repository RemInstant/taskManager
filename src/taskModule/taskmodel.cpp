#include "taskmodel.h"
#include "qjsonobject.h"

#include <QFile>
#include <QTextStream>

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel{parent}
{
    dat = QList<QJsonObject>();

    dat.push_back({{"name", "Заголовок 1"}, {"time", "00.00.0000 00:00"}, {"desc", "ОПИСАНИЕ ОПИСАНИЕ ОПИСАНИЕ"}, {"show", true}});
    dat.push_back({{"name", "Заголовок 2"}, {"time", "00.00.0000 00:00"}, {"desc", "ОПИСАНИЕ ОПИСАНИЕ ОПИСАНИЕ"}, {"show", true}});
    dat.push_back({{"name", "Заголовок 3"}, {"time", "00.00.0000 00:00"}, {"desc", "ОПИСАНИЕ ОПИСАНИЕ ОПИСАНИЕ"}, {"show", true}});
    dat.push_back({{"name", "Заголовок 4"}, {"time", "00.00.0000 00:00"}, {"desc", "ОПИСАНИЕ ОПИСАНИЕ ОПИСАНИЕ"}, {"show", true}});
    dat.push_back({{"name", "Заголовок 5"}, {"time", "00.00.0000 00:00"}, {"desc", "ОПИСАНИЕ ОПИСАНИЕ ОПИСАНИЕ"}, {"show", true}});
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return dat.size() - parent.row(); // ???

    return dat.size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    QString name = dat[index.row()].value("name").toString();
    QString time = dat[index.row()].value("time").toString();
    QString desc = dat[index.row()].value("desc").toString();

    switch(role)
    {
    case Qt::DisplayRole:
        return name+"\n"+time+"\n"+desc;
    case Qt::UserRole:
        return dat[index.row()]; // display raw
    case Qt::EditRole:
        qDebug() << "editRole data";
        return QVariant();
    default:
        //qDebug() << "defaultRole data";
        return QVariant();
    }
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setdata";
    if(index.isValid() && role == Qt::EditRole)
    {
        dat.replace(index.row(), value.toJsonObject());
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool TaskModel::insertRows(int row, int count, const QModelIndex &parent)
{
    row = std::min(dat.size(), row);

    QJsonObject base = {
        {"name", "Заголовок"},
        {"time", "00.00.0000 00:00"},
        {"desc", "Описание"},
        {"show", false}
    };

    this->beginInsertRows(parent, row, row+count-1);
    for(int i = 0; i < count; ++i)
    {
        dat.insert(row, base); // not a copy
    }
    this->endInsertRows();

    return true;
}

bool TaskModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row >= dat.size())
        return false;

    this->beginRemoveRows(parent, row, row+count-1);
    dat.erase(dat.begin()+row, dat.begin() + std::min(dat.size(), row+count));
    this->endRemoveRows();

    return true;
}

void TaskModel::saveData(QString path)
{
    QFile file(path + "/TaskData.json");

    if(file.open(QIODevice::Truncate | QIODevice::ReadWrite))
    {
        QJsonArray arr;
        for(QJsonObject val : dat)
        {
            arr.append(val);
        }

        QJsonDocument doc;
        doc.setArray(arr);
        file.write(doc.toJson());
        file.close();
    }
}

void TaskModel::loadData(QString path)
{
    QFile file(path + "/TaskData.json");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonArray arr = doc.array();

        dat.clear();
        for(QJsonValue val : arr)
        {
            dat.append(val.toObject());
        }

        file.close();
    }
}
