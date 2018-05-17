#include "rowhoverdelegate.hpp"

/*
 * Constructor.
 *
 * :param table: table
 * :param parent: parent, default nullptr
 */
RowHoverDelegate::RowHoverDelegate(QTableWidget *table, QObject *parent) :
    QStyledItemDelegate(parent),
    pm_table(table),
    m_row(-1)
{
    pm_table->setMouseTracking(true);
    connect(pm_table, SIGNAL(itemEntered(QTableWidgetItem *)), this, SLOT(onItemEntered(QTableWidgetItem *)));
}

/*
 * Item entered event.
 *
 * :param item: item
 */
void RowHoverDelegate::onItemEntered(QTableWidgetItem *item)
{
    m_row = item->row();
    pm_table->viewport()->update();
}

/*
 * Paint event.
 *
 * :param painter: painter
 * :param option: option
 * :param index: index
 */
void RowHoverDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    if (index.row() == m_row)
    {
        opt.state |= QStyle::State_MouseOver;
    }
    QStyledItemDelegate::paint(painter, opt, index);
}
