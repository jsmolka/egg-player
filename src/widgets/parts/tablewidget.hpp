#ifndef TABLEWIDGET_HPP
#define TABLEWIDGET_HPP

#include "core/globals.hpp"
#include "widgets/parts/clickablestyle.hpp"
#include "widgets/parts/rowhoverdelegate.hpp"
#include "widgets/parts/smoothtablewidget.hpp"

class TableWidget : public SmoothTableWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);

signals:
    void hoverRowChanged(int row);

protected:
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void onEntered(const QModelIndex &index);
    void onHoverRowChanged(int row);

private:
    void setup();

    RowHoverDelegate m_delegate;
    ClickableStyle m_style;
};

#endif // TABLEWIDGET_HPP
