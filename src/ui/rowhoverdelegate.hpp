#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QTableWidget *tableWidget, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected slots:
    void onItemEntered(QTableWidgetItem *item);

private:
    QTableWidget *pm_tableWidget;
    int m_hoveredRow;
};

#endif // ROWHOVERDELEGATE_HPP
