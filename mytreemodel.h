#ifndef MYTREEMODEL_H
#define MYTREEMODEL_H

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QQuickItem>

class myTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QStandardItem *rootItem;

    explicit myTreeModel(QObject *parent = nullptr);
    ~myTreeModel();
    Q_INVOKABLE QString nodename(QStandardItem *node);
    bool createparent(QString parent);
    bool appendtoparent(QString parent, QString child, QQuickItem* item);
    Q_INVOKABLE void removechild(QModelIndex index);
    Q_INVOKABLE bool is_parent(QModelIndex index);
    int rowcount(QModelIndex index);
    QQuickItem* rowItem(QModelIndex index);
    //  void select(QModelIndex index);

private:


};


#endif // MYTREEMODEL_H
