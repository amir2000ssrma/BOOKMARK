#include "myproxymodel.h"
#include "mytreemodel.h"

Myproxymodel::Myproxymodel()
{

}

Myproxymodel::~Myproxymodel()
{

}

QString Myproxymodel::searchedText() const
{
    return m_searchedText;
}

void Myproxymodel::setSearchedTask(const QString &newSearchedText)
{
    if (m_searchedText == newSearchedText)
        return;
    m_searchedText = newSearchedText;
    emit searchedTaskChanged();

    invalidateFilter();
}

void Myproxymodel::proxyremovechild(QModelIndex index)
{
    dynamic_cast<myTreeModel*>(sourceModel())->removechild(mapToSource(index));
}

bool Myproxymodel::proxy_is_parent(QModelIndex index)
{
    return dynamic_cast<myTreeModel*>(sourceModel())->is_parent(mapToSource(index));
}

int Myproxymodel::proxy_rowcount(QModelIndex index)
{
    return dynamic_cast<myTreeModel*>(sourceModel())->rowcount(mapToSource(index));
}

QQuickItem* Myproxymodel::rowItem(QModelIndex index)
{
    return dynamic_cast<myTreeModel*>(sourceModel())->rowItem(mapToSource(index));
}

//void Myproxymodel::proxyselect(QModelIndex index)
//{
//    QItemSelection selection(index, index);
//    m_selectionModel->select(selection, QItemSelectionModel::Select);
//}

//QItemSelectionModel* Myproxymodel::selectionmodel()
//{
//    return m_selectionModel;
//}

bool Myproxymodel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexText = sourceModel()->index(sourceRow, 0, sourceParent);

    if(sourceModel()->data(indexText).toString().toLower().contains(m_searchedText.toLower()))
        return true;

    int childCount = sourceModel()->rowCount(indexText);
    for(int i=0; i<childCount; i++) {
        if(filterAcceptsRow(i, indexText)) {
            return true;
        }
    }

    return false;
}

