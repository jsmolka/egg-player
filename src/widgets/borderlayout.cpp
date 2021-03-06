#include "borderlayout.hpp"

BorderLayout::BorderLayout(int margin, int spacing, QWidget *parent)
    : QLayout(parent)
{
    setMargin(margin);
    setSpacing(spacing);
}

BorderLayout::BorderLayout(int spacing, QWidget *parent)
    : BorderLayout(0, spacing, parent)
{

}

BorderLayout::~BorderLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void BorderLayout::add(QLayoutItem *item, Position position)
{
    ItemWrapper *wrapper = new ItemWrapper;
    wrapper->item = item;
    wrapper->position = position;
    m_items << wrapper;
}

void BorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

void BorderLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

int BorderLayout::count() const
{
    return m_items.size();
}

QLayoutItem *BorderLayout::itemAt(int index) const
{
    ItemWrapper *wrapper = m_items.value(index);

    return wrapper ? wrapper->item : nullptr;
}

QLayoutItem *BorderLayout::takeAt(int index)
{
    if (index < 0 || index >= m_items.size())
        return nullptr;

    return m_items.takeAt(index)->item;
}

void BorderLayout::setGeometry(const QRect &rect)
{
    ItemWrapper *center = nullptr;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;

    QLayout::setGeometry(rect);

    for (ItemWrapper *wrapper : qAsConst(m_items))
    {
        QLayoutItem *item = wrapper->item;
        const Position position = wrapper->position;

        if (position == Position::North)
        {
            item->setGeometry(QRect(
                rect.x(),
                northHeight,
                rect.width(),
                item->sizeHint().height()
            ));
            northHeight += item->geometry().height() + spacing();
        }
        else if (position == Position::South)
        {
            item->setGeometry(QRect(
                item->geometry().x(),
                item->geometry().y(),
                rect.width(),
                item->sizeHint().height()
            ));
            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(
                rect.x(),
                rect.y() + rect.height() - southHeight + spacing(),
                item->geometry().width(),
                item->geometry().height()
            ));
        }
        else if (position == Position::Center)
        {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (ItemWrapper *wrapper : qAsConst(m_items))
    {
        QLayoutItem *item = wrapper->item;
        const Position position = wrapper->position;

        if (position == Position::West)
        {
            item->setGeometry(QRect(
                rect.x() + westWidth,
                northHeight,
                item->sizeHint().width(),
                centerHeight
            ));
            westWidth += item->geometry().width() + spacing();
        }
        else if (position == Position::East)
        {
            item->setGeometry(QRect(
                item->geometry().x(),
                item->geometry().y(),
                item->sizeHint().width(),
                centerHeight
            ));
            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(
                rect.x() + rect.width() - eastWidth + spacing(),
                northHeight,
                item->geometry().width(),
                item->geometry().height()
            ));
        }
    }

    if (center)
    {
        center->item->setGeometry(QRect(
            westWidth,
            northHeight,
            rect.width() - eastWidth - westWidth,
            centerHeight
        ));
    }
}

QSize BorderLayout::minimumSize() const
{
    return calculateSize(SizeType::MinimumSize);
}

QSize BorderLayout::sizeHint() const
{
    return calculateSize(SizeType::SizeHint);
}

QSize BorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;
    for (ItemWrapper *wrapper : qAsConst(m_items))
    {
        QSize itemSize;
        const Position position = wrapper->position;

        if (sizeType == SizeType::MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else
            itemSize = wrapper->item->sizeHint();

        if (position == Position::North
                || position == Position::South
                || position == Position::Center)
            totalSize.rheight() += itemSize.height();

        if (position == Position::West
                || position == Position::East
                || position == Position::Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}
