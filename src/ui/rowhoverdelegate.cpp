#include "rowhoverdelegate.hpp"

/*
 * Constructor.
 *
 * :param tableWidget: widget
 * :param parent: parent, default nullptr
 */
RowHoverDelegate::RowHoverDelegate(QTableWidget *tableWidget, QObject *parent) :
    QStyledItemDelegate(parent),
    pm_tableWidget(tableWidget),
    m_hoveredRow(-1)
{
    pm_tableWidget->setMouseTracking(true);
    connect(pm_tableWidget, SIGNAL(itemEntered(QTableWidgetItem *)), this, SLOT(onItemEntered(QTableWidgetItem *)));
}

/*
 * Item entered event.
 *
 * :param item: item
 */
void RowHoverDelegate::onItemEntered(QTableWidgetItem *item)
{
    m_hoveredRow = item->row();
    pm_tableWidget->viewport()->update();
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
    if (index.row() == m_hoveredRow)
    {
        opt.state |= QStyle::State_MouseOver;
    }
    QStyledItemDelegate::paint(painter, opt, index);
}