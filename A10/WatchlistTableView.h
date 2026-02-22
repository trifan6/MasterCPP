#pragma once
#include <QAbstractTableModel>
#include "UserService.h"

class WatchlistTableView : public QAbstractTableModel {
    Q_OBJECT
private:
    UserService& userService;
public:
    WatchlistTableView(UserService& service, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

