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
    pm_table->viewport()->setMouseTracking(true);
    connect(pm_table, SIGNAL(mouseLeft()), this, SLOT(onMouseLeft()));
    connect(pm_table, SIGNAL(entered(QModelIndex)), this, SLOT(onEntered(QModelIndex)));
}

/*
 * Item entered.
 *
 * :param index: index
 */
void RowHoverDelegate::onEntered(QModelIndex index)
{
    m_row = index.row();
    pm_table->viewport()->update();
}

/*
 * Mouse left.
 */
void RowHoverDelegate::onMouseLeft()
{
    m_row = -1;
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
