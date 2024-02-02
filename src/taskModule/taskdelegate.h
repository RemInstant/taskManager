#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QApplication>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextDocument>
#include <QJsonObject>
#include <QTime>

#include <QDebug>

#include "taskmodel.h"
#include "taskeditor.h"


class TaskDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    QModelIndex lastClickedIndex;
    QTime t;

public:
    explicit TaskDelegate(QObject *parent = nullptr);
    void setLastClicked(const QModelIndex &index, bool toEmit = true);

public slots:
    void onTaskClicked(const QModelIndex &index);
    void onTaskDoubleClicked(const QModelIndex &index);

protected:
    void paint (QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TASKDELEGATE_H
