#include "customquerymodel.h"
#include <QSqlRecord>
#include <QSqlQuery>


CustomQueryModel::CustomQueryModel(QObject *parent): QSqlQueryModel (parent)
{

}

QVariant CustomQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (index.isValid()) {
            if (role < Qt::UserRole) {
                value = QSqlQueryModel::data(index, role);
            } else {
                int columnIdx = role - Qt::UserRole - 1;
                QModelIndex modelIndex = this->index(index.row(), columnIdx);
                value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
            }
        }
    return value;
}

QHash<int, QByteArray> CustomQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        // record() returns an empty QSqlRecord
        for (int i = 0; i < this->record().count(); i ++) {
            roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
        }
    return roles;
}
