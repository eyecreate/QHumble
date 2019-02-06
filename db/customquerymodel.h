#ifndef CUSTOMQUERYMODEL_H
#define CUSTOMQUERYMODEL_H

#include <QSqlQueryModel>
#include <QVariant>
#include <QHash>
#include <QModelIndex>

class CustomQueryModel : public QSqlQueryModel
{
public:
    CustomQueryModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;
};

#endif // CUSTOMQUERYMODEL_H
