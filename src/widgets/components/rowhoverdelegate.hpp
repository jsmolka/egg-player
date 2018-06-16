#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

signals:
    void hoverRowChanged(int);
};

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QTableWidget *table, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private slots:
    void onRowChanged(int row);

private:
    TableWidget *pm_table;
    int m_row;
};

#endif // ROWHOVERDELEGATE_HPP
