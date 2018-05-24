#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QTableWidget>

/*
 * Create a custom widget to process events because I am too stupid for forward
 * declaration and moving the class into the same file is ugly.
 */
class TableWidget : public QTableWidget
{
    Q_OBJECT

signals:
    void rowChanged(int);
};

/*
 * This class is made specifically for the MusicLibrary class and some functions
 * might not work for other classes.
 */
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
