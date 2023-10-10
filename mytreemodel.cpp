#include "mytreemodel.h"

#include <QStandardItemModel>
#include <QStandardItem>

myTreeModel::myTreeModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setColumnCount(1);
    rootItem = invisibleRootItem();
}

myTreeModel::~myTreeModel(){

}

QString myTreeModel::nodename(QStandardItem *node)
{
    return node->text();
}

bool myTreeModel::createparent(QString parent)
{
    bool created = true;

    for(int i=0; i < rootItem->rowCount(); i++){
        if(rootItem->child(i)->text() == parent){
            created = false;
            break;
        }
    }
    if(created){
        QStandardItem *node = new QStandardItem;
        rootItem->appendRow(node);
        node->setText(parent);
        return created;
    }
    else{
        return created;
    }
}

bool myTreeModel::appendtoparent(QString parent, QString child, QQuickItem* item)
{

    bool is_ok = false;
    int row = 0;
    for(int i=0; i < rootItem->rowCount(); i++){
        if(rootItem->child(i)->text() == parent){
            is_ok = true;
            row = i;
            break;
        }
    }
    if(is_ok){
        QStandardItem *node = new QStandardItem;
        node->setText(child);
        QVariant variant = QVariant::fromValue(item);
        node->setData(variant,2000);

        rootItem->child(row)->appendRow(node);
        return is_ok;
    }
    else
        return is_ok;
}

void myTreeModel::removechild(QModelIndex index)
{
    const QStandardItemModel* model = static_cast<const QStandardItemModel*>(index.model());
    QStandardItem* node = model->itemFromIndex(index);
    QStandardItem* par = node->parent();
    par->removeRow(node->row());
    if(par->rowCount() == 0){
        rootItem->removeRow(par->row());
    }

}

bool myTreeModel::is_parent(QModelIndex index)
{
    const QStandardItemModel* model = static_cast<const QStandardItemModel*>(index.model());
    QStandardItem* node = model->itemFromIndex(index);
    if(node->parent() == nullptr)
        return true;
    else
        return false;
}

int myTreeModel::rowcount(QModelIndex index)
{
    const QStandardItemModel* model = static_cast<const QStandardItemModel*>(index.model());
    QStandardItem* node = model->itemFromIndex(index);
    return node->rowCount();
}


QQuickItem* myTreeModel::rowItem(QModelIndex index)
{
    auto item = data(index, 2000).value<QQuickItem*>();
    return item;
}

//void myTreeModel::select(QModelIndex index)
//{
//    QItemSelection selection(createIndex(0,0), createIndex(0,0));
//    m_selectionModel->select(selection, QItemSelectionModel::Select);
//}



