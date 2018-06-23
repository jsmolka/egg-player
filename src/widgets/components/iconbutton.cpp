#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
    , m_lockable(false)
    , m_locked(false)
    , m_index(0)
{
    setup();

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
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
    setIcon(m_icons[m_index]);
}

int IconButton::index() const
{
    return m_index;
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

void IconButton::setLockable(bool lockable)
{
    m_lockable = lockable;
}

bool IconButton::isLockable() const
{
    return m_lockable;
}

void IconButton::setSize(const QSize &size)
{
    setIconSize(size);
    setFixedSize(size);
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
