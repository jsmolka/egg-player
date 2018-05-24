#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

/*
 * Create a custom widget to process the leave event because I am too stupid for
 * forward declaration and moving the class into the same file is ugly.
 */
class TableWidget : public QTableWidget
{
    Q_OBJECT

signals:
    void mouseLeft();
};

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QTableWidget *table, QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private slots:
    void onEntered(QModelIndex index);
    void onMouseLeft();

private:
    TableWidget *pm_table;
    int m_row;
};

#endif // ROWHOVERDELEGATE_HPP
