#ifndef TABLEWIDGET_HPP
#define TABLEWIDGET_HPP

#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidget>

#include "rowhoverdelegate.hpp"
#include "clickablestyle.hpp"

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

signals:
    void hoverRowChanged(int);

protected:
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void onEntered(QModelIndex index);
    void onRowChanged(int row);

private:
    void setup();

    RowHoverDelegate *pm_delegate;
};

#endif // TABLEWIDGET_HPP
