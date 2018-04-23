#include "borderlayout.hpp"

/*
 * Constructor.
 *
 * :param margin: margin
 * :param spacing: spacing
 * :param parent: parent
 */
BorderLayout::BorderLayout(int margin, int spacing, QWidget *parent) : QLayout(parent)
{
    setMargin(margin);
    setSpacing(spacing);
}

/*
 * Constructor.
 *
 * :param spacing: spacing
 * :param parent: parent
 */
BorderLayout::BorderLayout(int spacing, QWidget *parent) : QLayout(parent)
{
    setSpacing(spacing);
}

/*
 * Destructor.
 */
BorderLayout::~BorderLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

/*
 * Adds item to layout west position.
 *
 * :param item: item
 */
void BorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

/*
 * Adds widget at position.
 *
 * :param widget: widget
 * :param position: position
 */
void BorderLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

/*
 * Returns item count.
 *
 * :return: item count
 */
int BorderLayout::count() const
{
    return m_items.size();
}

/*
 * Returns item pointer at index. Returns
 * nullptr if there is not item at the index.
 *
 * :param index: index
 * :return: wrapper pointer or nullptr
 */
QLayoutItem * BorderLayout::itemAt(int index) const
{
    ItemWrapper *wrapper = m_items.value(index);
    return wrapper ? wrapper->item : nullptr;
}

/*
 * Returns minimum size.
 *
 * :return: minimum size
 */
QSize BorderLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

/*
 * Sets geometry.
 *
 * :param rect: rectangle
 */
void BorderLayout::setGeometry(const QRect &rect)
{
    ItemWrapper *center = 0;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;

    QLayout::setGeometry(rect);

    for (int i = 0; i < m_items.size(); i++) {
        ItemWrapper *wrapper = m_items.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == North)
        {
            item->setGeometry(QRect(rect.x(),
                                    northHeight,
                                    rect.width(),
                                    item->sizeHint().height()));

            northHeight += item->geometry().height() + spacing();
        }
        else if (position == South)
        {
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(),
                                    rect.width(),
                                    item->sizeHint().height()));

            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(),
                                    rect.y() + rect.height() - southHeight + spacing(),
                                    item->geometry().width(),
                                    item->geometry().height()));
        }
        else if (position == Center)
        {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (int i = 0; i < m_items.size(); i++)
    {
        ItemWrapper *wrapper = m_items.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == West)
        {
            item->setGeometry(QRect(rect.x() + westWidth,
                                    northHeight,
                                    item->sizeHint().width(),
                                    centerHeight));

            westWidth += item->geometry().width() + spacing();
        }
        else if (position == East)
        {
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(),
                                    item->sizeHint().width(),
                                    centerHeight));

            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(rect.x() + rect.width() - eastWidth + spacing(),
                                    northHeight,
                                    item->geometry().width(),
                                    item->geometry().height()));
        }
    }

    if (center)
        center->item->setGeometry(QRect(westWidth,
                                        northHeight,
                                        rect.width() - eastWidth - westWidth,
                                        centerHeight));
}

/*
 * Returns size hint.
 *
 * :return: size
 */
QSize BorderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

/*
 * Takes item at index. Returns item pointer
 * if the index exists else a nullptr.
 *
 * :param index: index
 * :return: item pointer or nullptr
 */
QLayoutItem * BorderLayout::takeAt(int index)
{
    if (index >= 0 && index < m_items.size())
    {
        ItemWrapper *layoutStruct = m_items.takeAt(index);
        return layoutStruct->item;
    }
    return nullptr;
}

/*
 * Adds layout item at position.
 *
 * :param item: item
 * :param position: position
 */
void BorderLayout::add(QLayoutItem *item, Position position)
{
    m_items.append(new ItemWrapper(item, position));
}

/*
 * Calculates size.
 *
 * :param sizeType: size type
 * :return: calculated size
 */
QSize BorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;

    for (int i = 0; i < m_items.size(); i++)
    {
        ItemWrapper *wrapper = m_items.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if (sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else
            itemSize = wrapper->item->sizeHint();

        if (position == North
                || position == South
                || position == Center)
            totalSize.rheight() += itemSize.height();

        if (position == West
                || position == East
                || position == Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}
