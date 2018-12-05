#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>

#include "core/macros.hpp"

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QObject *parent = nullptr);

    EGG_P_PROP(int, hoverRow, setHoverRow, hoverRow)

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ROWHOVERDELEGATE_HPP
