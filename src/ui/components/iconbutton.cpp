#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent) : QPushButton(parent)
{
    m_selected = true;
    m_lockable = false;
    m_locked = false;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(switchLocked(void)));
}

void IconButton::setIcon1(QIcon icon)
{
    m_icon1 = icon;
}

QIcon IconButton::icon1() const
{
    return m_icon1;
}

void IconButton::setIcon2(QIcon icon)
{
    m_icon2 = icon;
}

QIcon IconButton::icon2() const
{
    return m_icon2;
}

void IconButton::setSelected(bool selected)
{
    m_selected = selected;

    setSelectedIcon();
}

void IconButton::setSelected(int selected)
{
    setSelected((bool)selected);
}

bool IconButton::isSelected() const
{
    return m_selected;
}

void IconButton::setLockable(bool lockable)
{
    m_lockable = lockable;
}

void IconButton::setLocked(bool locked)
{
    m_locked = locked;
}

bool IconButton::isLocked() const
{
    return m_locked;
}

void IconButton::init(QIcon icon, QSize size)
{
   init(icon, QIcon(), size);
}

void IconButton::init(QIcon icon1, QIcon icon2, QSize size)
{
    m_icon1 = icon1;
    m_icon2 = icon2;

    setIcon(m_icon1);
    setIconSize(size);
    setFixedSize(size);
}

void IconButton::switchIcon()
{
    setSelected(!m_selected);
}

void IconButton::switchLocked()
{
    if (m_lockable)
    {
        m_locked = !m_locked;
        style()->unpolish(this);
        style()->polish(this);

        if (isLocked())
            emit locked();
    }
}

void IconButton::setSelectedIcon()
{
    if (m_selected)
        setIcon(m_icon1);
    else
        setIcon(m_icon2);
}
