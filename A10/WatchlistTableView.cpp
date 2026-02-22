#include "WatchlistTableView.h"

WatchlistTableView::WatchlistTableView(UserService& service, QObject* parent)
    : QAbstractTableModel(parent), userService(service) {}

int WatchlistTableView::rowCount(const QModelIndex& parent) const {
    try {
        return userService.see_watch_list().size();
    } catch (...) {
        return 0;
    }
}

int WatchlistTableView::columnCount(const QModelIndex& parent) const {
    return 5; // Title, Presenter, Duration, Likes, Link
}

QVariant WatchlistTableView::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole || !index.isValid()) {
        return QVariant();
    }

    try {
        vector<Tutorial> watchlist = userService.see_watch_list();
        if (index.row() >= watchlist.size()) {
            return QVariant();
        }

        Tutorial& t = watchlist[index.row()];
        switch (index.column()) {
            case 0: return QString::fromStdString(t.get_title());
            case 1: return QString::fromStdString(t.get_presenter());
            case 2: return QString("%1:%2").arg(t.get_minutes()).arg(t.get_seconds(), 2, 10, QChar('0'));
            case 3: return t.get_likes();
            case 4: return QString::fromStdString(t.get_link());
            default: return QVariant();
        }
    } catch (...) {
        return QVariant();
    }
}

QVariant WatchlistTableView::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case 0: return "Title";
        case 1: return "Presenter";
        case 2: return "Duration";
        case 3: return "Likes";
        case 4: return "Link";
        default: return QVariant();
    }
}