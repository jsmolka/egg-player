#ifndef BORDERLAYOUT_HPP
#define BORDERLAYOUT_HPP

#include <QLayout>
#include <QRect>

class BorderLayout : public QLayout
{
    Q_OBJECT

public:
    enum Position {North, East, South, West, Center};

    BorderLayout(int margin = 0, int spacing = -1, QWidget *parent = 0);
    BorderLayout(int spacing = -1, QWidget *parent = 0);
    ~BorderLayout();

    void addItem(QLayoutItem *item) override;
    void addWidget(QWidget *widget, Position position);
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

    void add(QLayoutItem *item, Position position);

private:
    struct ItemWrapper
    {
        ItemWrapper(QLayoutItem *i, Position p) {
            item = i;
            position = p;
        }

        QLayoutItem *item;
        Position position;
    };

    enum SizeType {MinimumSize, SizeHint};
    QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper *> m_items;
};

#endif // BORDERLAYOUT_HPP
