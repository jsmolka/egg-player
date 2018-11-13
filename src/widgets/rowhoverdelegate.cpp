#include "rowhoverdelegate.hpp"

RowHoverDelegate::RowHoverDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_hoverRow(-1)
{

}

void RowHoverDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);

    if (index.row() == m_hoverRow)
        opt.state |= QStyle::State_MouseOver;
    else
        opt.state &= ~QStyle::State_MouseOver;

    QStyledItemDelegate::paint(painter, opt, index);
}
