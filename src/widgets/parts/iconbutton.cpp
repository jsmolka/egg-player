#include "iconbutton.hpp"

#include <QEvent>

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
    , m_iconIndex(0)
{
    setup();
}

void IconButton::setIcons(const QVector<QIcon> &icons)
{
    m_icons = icons;

    if (!icons.isEmpty())
        setIcon(icons.first());
}

QVector<QIcon> IconButton::icons() const
{
    return m_icons;
}

void IconButton::setIconIndex(int index)
{
    if (m_icons.length() <= index)
        return;

    m_iconIndex = index;
    setIcon(m_icons.at(index));
}

int IconButton::iconIndex() const
{
    return m_iconIndex;
}

void IconButton::setSize(const QSize &size)
{
    setFixedSize(size);
    setIconSize(size);
}

bool IconButton::event(QEvent *event)
{
    if (event->type() == QEvent::HoverEnter)
    {
        setIcon(m_icons.at(m_iconIndex).pixmap(size(), QIcon::Active));
        return true;
    }
    if (event->type() == QEvent::HoverLeave)
    {
        setIcon(m_icons.at(m_iconIndex).pixmap(size(), QIcon::Normal));
        return true;
    }
    return QPushButton::event(event);
}

void IconButton::setup()
{
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
