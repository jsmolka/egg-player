#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QTableWidget *table, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected slots:
    void onItemEntered(QTableWidgetItem *item);

private:
    QTableWidget *pm_table;
    int m_row;
};

#endif // ROWHOVERDELEGATE_HPP
