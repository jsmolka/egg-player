#ifndef TABLEWIDGET_HPP
#define TABLEWIDGET_HPP

#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidget>

#include "clickablestyle.hpp"
#include "rowhoverdelegate.hpp"
#include "smoothtablewidget.hpp"

class TableWidget : public SmoothTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

signals:
    void hoverRowChanged(int row);

protected:
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void onEntered(QModelIndex index);
    void onHoverRowChanged(int row);

private:
    void setup();

    RowHoverDelegate *pm_delegate;
};

#endif // TABLEWIDGET_HPP
