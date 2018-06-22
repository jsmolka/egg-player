#include "tablewidget.hpp"

TableWidget::TableWidget(QWidget *parent)
    : QTableWidget(parent)
    , pm_delegate(new RowHoverDelegate(this))
{
    setup();

    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(onEntered(QModelIndex)));
    connect(this, SIGNAL(hoverRowChanged(int)), this, SLOT(onRowChanged(int)));

    connect(this, SIGNAL(hoverRowChanged(int)), pm_delegate, SLOT(setHoverRow(int)));
}

TableWidget::~TableWidget()
{

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

void TableWidget::onEntered(QModelIndex index)
{
    emit hoverRowChanged(index.row());
}

void TableWidget::onRowChanged(int row)
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
    setItemDelegate(pm_delegate);
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setWordWrap(false);

    horizontalHeader()->hide();
    verticalHeader()->hide();

    verticalScrollBar()->setStyle(new ClickableStyle(style()));
}
