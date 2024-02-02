#include "taskdelegate.h"

TaskDelegate::TaskDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
    lastClickedIndex = QModelIndex();
    t = QTime::currentTime();
}

void TaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug() << "DRAW" << index.row();

    QJsonObject val = index.data(Qt::UserRole).toJsonObject();
    QString name = val.value("name").toString();
    QString time = val.value("time").toString();
    QString desc = val.value("desc").toString();
    bool show = val.value("show").toBool(false);

    if (!show) return;

    QStyleOptionViewItem options = option;  // unconst
    initStyleOption(&options, index);       // ??

    // save (x0;y0) pos and mb smth else
    painter->save();

    QRect textContainer = options.rect;
    textContainer.setWidth(textContainer.width() - 20);
    textContainer.setHeight(textContainer.width() - 20);
    textContainer.translate(10, 10);

    QFont titleFont = options.font;
    titleFont.setWeight(QFont::Bold);

    QFontMetrics titleMetrics(titleFont);

    int textFlags = Qt::AlignLeft | Qt::TextWordWrap;

    QRect titleRect = textContainer;
    titleRect.setHeight(titleMetrics.boundingRect(textContainer, textFlags, name).height());

    painter->setFont(titleFont);
    painter->drawText(titleRect, textFlags, name);

    if (index.row() == lastClickedIndex.row())
    {
        QFont descFont = options.font;

        QFontMetrics descMetrics(descFont);

        QRect descRect = textContainer;
        descRect.setHeight(descMetrics.boundingRect(textContainer, textFlags, desc).height());
        descRect.translate(0, titleRect.height());

        painter->setFont(descFont);
        painter->drawText(descRect, textFlags, desc);
    }

    options.text = "";
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    // restore initial painter
    painter->restore();
}

QSize TaskDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QJsonObject val = index.data(Qt::UserRole).toJsonObject();
    QString name = val.value("name").toString();
    QString time = val.value("time").toString();
    QString desc = val.value("desc").toString();
    bool show = val.value("show").toBool(false);

    if (!show) return QSize(0, 0);

    QStyleOptionViewItem options = option;
    initStyleOption(&options, index); 

    QRect textContainer = options.rect;
    textContainer.setWidth(textContainer.width() - 20);
    textContainer.setHeight(textContainer.width() - 20);
    textContainer.translate(10, 10);

    int finalHeight = 20;

    QFont titleFont = options.font;
    titleFont.setWeight(QFont::Bold);

    QFontMetrics titleMetrics(titleFont);

    int textFlags = Qt::AlignLeft | Qt::TextWordWrap;

    finalHeight += titleMetrics.boundingRect(textContainer, textFlags, name).height();

    if (index.row() == lastClickedIndex.row())
    {
        QFont descFont = options.font;
        QFontMetrics descMetrics(descFont);
        finalHeight += descMetrics.boundingRect(textContainer, textFlags, desc).height();
    }

    return QSize(options.rect.width(), finalHeight);
}

QWidget *TaskDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    TaskEditor *editor = new TaskEditor(parent);

    return editor;
}

void TaskDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QJsonObject val = index.data(Qt::UserRole).toJsonObject();

    TaskEditor *tEditor = static_cast<TaskEditor*>(editor);
    tEditor->setData(val);
}

void TaskDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TaskEditor *tEditor = static_cast<TaskEditor*>(editor);
    TaskModel *tModel = static_cast<TaskModel*>(model);

    tModel->setData(index, tEditor->getData());
}

void TaskDelegate::updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return;
}

void TaskDelegate::setLastClicked(const QModelIndex &index, bool toEmit)
{
    if (!index.isValid()) return;

    lastClickedIndex = index;
    if (toEmit) emit this->sizeHintChanged(index);
}

void TaskDelegate::onTaskClicked(const QModelIndex &index)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier ||
            QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        return;
    }
    if (index.isValid())
    {
        lastClickedIndex = index;
    }
    else
    {
        lastClickedIndex = QModelIndex();
    }

    emit this->sizeHintChanged(index);
}

void TaskDelegate::onTaskDoubleClicked(const QModelIndex &index)
{
    // TO DELETE OR NOT TO DELETE
    lastClickedIndex = index;
    emit this->sizeHintChanged(index);
}
