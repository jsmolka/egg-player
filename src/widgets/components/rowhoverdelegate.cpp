#include "rowhoverdelegate.hpp"

RowHoverDelegate::RowHoverDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_hoverRow(-1)
{

}

RowHoverDelegate::~RowHoverDelegate()
{

}

int RowHoverDelegate::hoverRow() const
{
    return m_hoverRow;
}

void RowHoverDelegate::setHoverRow(int hoverRow)
{
    m_hoverRow = hoverRow;
}

void RowHoverDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    if (index.row() == m_hoverRow)
        opt.state |= QStyle::State_MouseOver;

    QStyledItemDelegate::paint(painter, opt, index);
}
