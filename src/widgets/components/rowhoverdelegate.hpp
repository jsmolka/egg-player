#ifndef ROWHOVERDELEGATE_HPP
#define ROWHOVERDELEGATE_HPP

#include <QStyledItemDelegate>

class RowHoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    RowHoverDelegate(QObject *parent = nullptr);
    ~RowHoverDelegate();

    int hoverRow() const;

public slots:
    void setHoverRow(int hoverRow);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int m_hoverRow;
};

#endif // ROWHOVERDELEGATE_HPP
