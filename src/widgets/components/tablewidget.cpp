#include "tablewidget.hpp"

#include <QHeaderView>
#include <QScrollBar>

#include "clickablestyle.hpp"

TableWidget::TableWidget(QWidget *parent)
    : SmoothTableWidget(parent)
    , m_delegate(new RowHoverDelegate(this))
{
    setup();

    connect(this, &TableWidget::entered, this, &TableWidget::onEntered);
    connect(this, &TableWidget::hoverRowChanged, this, &TableWidget::onHoverRowChanged);

    connect(this, &TableWidget::hoverRowChanged, m_delegate, &RowHoverDelegate::setHoverRow);
}

void TableWidget::leaveEvent(QEvent *event)
{
    emit hoverRowChanged(-1);

    QTableWidget::leaveEvent(event);
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);

    emit hoverRowChanged(indexAt(mapFromGlobal(QCursor::pos())).row());
}

void TableWidget::onEntered(const QModelIndex &index)
{
    emit hoverRowChanged(index.row());
}

void TableWidget::onHoverRowChanged(int row)
{
    Q_UNUSED(row);

    viewport()->update();
}

void TableWidget::setup()
{
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setItemDelegate(m_delegate);
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setWordWrap(false);

    horizontalHeader()->hide();
    verticalHeader()->hide();

    verticalScrollBar()->setStyle(new ClickableStyle);
}
