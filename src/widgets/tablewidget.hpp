#ifndef TABLEWIDGET_HPP
#define TABLEWIDGET_HPP

#include "widgets/clickablestyle.hpp"
#include "widgets/rowhoverdelegate.hpp"
#include "widgets/smoothtablewidget.hpp"

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
    void init();

    RowHoverDelegate m_delegate;
    ClickableStyle m_style;
};

#endif // TABLEWIDGET_HPP
