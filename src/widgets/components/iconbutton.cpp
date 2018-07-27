#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
    , m_lockable(false)
    , m_locked(false)
    , m_index(0)
{
    setup();

    connect(this, &IconButton::clicked, this, &IconButton::onClicked);
}

IconButton::~IconButton()
{

}

void IconButton::setIcons(const QVector<QIcon> &icons)
{
    m_icons = icons;
    setIcon(m_icons.first());
}

QVector<QIcon> IconButton::icons() const
{
    return m_icons;
}

void IconButton::setIndex(int index)
{
    m_index = index;
    setIcon(m_icons.at(m_index));
}

int IconButton::index() const
{
    return m_index;
}

void IconButton::setLockable(bool lockable)
{
    m_lockable = lockable;
}

bool IconButton::isLockable() const
{
    return m_lockable;
}

void IconButton::setLocked(bool locked)
{
    m_locked = locked;

    if (!m_lockable)
        return;

    style()->unpolish(this);
    style()->polish(this);

    emit this->locked(m_locked);
}

bool IconButton::isLocked() const
{
    return m_locked;
}

void IconButton::setSize(const QSize &size)
{
    setIconSize(size);
    setFixedSize(size);
}

bool IconButton::event(QEvent *event)
{
    if (event->type() == QEvent::HoverEnter)
    {
        setIcon(m_icons.at(m_index).pixmap(size(), QIcon::Active));
        return true;
    }

    if (event->type() == QEvent::HoverLeave)
    {
        setIcon(m_icons.at(m_index).pixmap(size(), QIcon::Normal));
        return true;
    }

    return QWidget::event(event);
}

void IconButton::onClicked()
{
    setLocked(!m_locked);
}

void IconButton::setup()
{
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
