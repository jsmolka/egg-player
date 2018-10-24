#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>

#include "core/globals.hpp"

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QObject *parent = nullptr);

    int hoverRow() const;

public slots:
    void setHoverRow(int row);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int m_hoverRow;
};

#endif // ROWHOVERDELEGATE_HPP
