#include "rowhoverdelegate.hpp"

/*
 * Constructor.
 *
 * :param table: table
 * :param parent: parent, default nullptr
 */
RowHoverDelegate::RowHoverDelegate(QTableWidget *table, QObject *parent) :
    QStyledItemDelegate(parent),
    pm_table(static_cast<TableWidget *>(table)),
    m_row(-1)
{
    connect(pm_table, SIGNAL(rowChanged(int)), this, SLOT(onRowChanged(int)));
}

/*
 * Sets the row and updates the widget if it is valid.
 *
 * :param row: row
 */
void RowHoverDelegate::onRowChanged(int row)
{
    m_row = row;
    if (m_row != -1)
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
        opt.state |= QStyle::State_MouseOver;

    QStyledItemDelegate::paint(painter, opt, index);
}
