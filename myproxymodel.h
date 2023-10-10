#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QItemSelectionModel>
#include <QQuickItem>

class Myproxymodel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString searchedText READ searchedText WRITE setSearchedTask NOTIFY searchedTaskChanged)
public:
    Myproxymodel();
    ~Myproxymodel();

    QString searchedText() const;
    void setSearchedTask(const QString &newSearchedText);
    Q_INVOKABLE void proxyremovechild(QModelIndex index);
    Q_INVOKABLE bool proxy_is_parent(QModelIndex index);
    Q_INVOKABLE int proxy_rowcount(QModelIndex index);
    Q_INVOKABLE QQuickItem* rowItem(QModelIndex index);
    // Q_INVOKABLE void proxyselect(QModelIndex index);
    //Q_INVOKABLE QItemSelectionModel* selectionmodel();
    //Q_INVOKABLE void select(int row);
signals:
    void searchedTaskChanged();


protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    QString m_searchedText;

};

#endif // MYPROXYMODEL_H
