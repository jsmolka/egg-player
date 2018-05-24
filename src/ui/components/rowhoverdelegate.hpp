#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

/*
 * Create a class which we can cast MusicLibrary to because I am too stupid for
 * forward declaration. It only contains the necessary signal.
 */
class TableWidget : public QTableWidget
{
    Q_OBJECT

signals:
    void rowChanged(int);
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
