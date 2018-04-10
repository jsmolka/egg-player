#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent) : QPushButton(parent)
{
    m_selected = true;
    m_lockable = false;
    m_locked = false;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

IconButton::~IconButton()
{

}

void IconButton::setIcons(const QList<QIcon> &icons)
{
    m_icons = icons;
}

QList<QIcon> IconButton::icons() const
{
    return m_icons;
}

void IconButton::setSelectedIcon(int selected)
{
    m_selected = selected;

    setIcon(m_icons[selected]);
}

int IconButton::selectedIcon() const
{
    return m_selected;
}

void IconButton::setLocked(bool locked)
{
    m_locked = locked;
}

bool IconButton::isLocked() const
{
    return m_locked;
}

void IconButton::setLockable(bool lockable)
{
    m_lockable = lockable;
}

bool IconButton::isLockable() const
{
    return m_lockable;
}

void IconButton::init(const QList<QIcon> &icons, int size, bool lockable)
{
    m_icons = icons;
    m_lockable = lockable;

    QSize iconSize = QSize(size, size);

    setIcon(icons[0]);
    setIconSize(iconSize);
    setFixedSize(iconSize);
}

void IconButton::onClicked()
{
    if (m_lockable)
    {
        m_locked = !m_locked;
        style()->unpolish(this);
        style()->polish(this);
        emit locked(m_locked);
    }
}
