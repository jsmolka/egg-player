#include "tablewidget.hpp"

#include <QHeaderView>
#include <QScrollBar>

TableWidget::TableWidget(QWidget *parent)
    : SmoothTableWidget(parent)
    , m_delegate(this)
{
    init();

    connect(this, &TableWidget::entered, this, &TableWidget::onEntered);
}

void TableWidget::leaveEvent(QEvent *event)
{
    setHoverRow(-1);

    SmoothTableWidget::leaveEvent(event);
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    SmoothTableWidget::resizeEvent(event);

    setHoverRow(indexAt(mapFromGlobal(QCursor::pos())).row());
}

void TableWidget::onEntered(const QModelIndex &index)
{
    setHoverRow(index.row());
}

void TableWidget::init()
{
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setItemDelegate(&m_delegate);
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setWordWrap(false);

    horizontalHeader()->hide();
    verticalHeader()->hide();

    verticalScrollBar()->setStyle(&m_style);
}

void TableWidget::setHoverRow(int row)
{
    if (row == m_delegate.hoverRow())
        return;

    m_delegate.setHoverRow(row);

    viewport()->update();
}
