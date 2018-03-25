#include "iconbutton.hpp"

IconButton::IconButton(bool autoSwitch, QWidget *parent) : QPushButton(parent)
{
    m_selected = true;
    m_locked = false;
    m_autoSwitch = autoSwitch;

    if (autoSwitch)
        connect(this, SIGNAL(clicked(bool)), this, SLOT(switchIcon(void)));
}

IconButton::IconButton(QWidget *parent)
{
    IconButton(true, parent);
}

void IconButton::setIcon1(QIcon icon)
{
    m_icon1 = icon;
}

void IconButton::setIcon1(QString path)
{
    setIcon1(QIcon(path));
}

QIcon IconButton::icon1() const
{
    return m_icon1;
}

void IconButton::setIcon2(QIcon icon)
{
    m_icon2 = icon;
}

void IconButton::setIcon2(QString path)
{
    setIcon2(QIcon(path));
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

bool IconButton::selected() const
{
    return m_selected;
}

void IconButton::setLocked(bool locked)
{
    m_locked = locked;
}

bool IconButton::locked() const
{
    return m_locked;
}

void IconButton::init(QString path, QSize size)
{
   init(path, QString(), size);
}

void IconButton::init(QString path1, QString path2, QSize size)
{
    setIcon1(path1);
    setIcon2(path2);

    setIcon(m_icon1);
    setIconSize(size);
    setFixedSize(size);
}

void IconButton::switchIcon()
{
    setSelected(!m_selected);
    m_locked = !m_locked;
}

void IconButton::setSelectedIcon()
{
    if (m_selected && !m_icon1.isNull())
    {
        setIcon(m_icon1);
    }
    else if (!m_icon2.isNull())
    {
        setIcon(m_icon2);
    }
}
