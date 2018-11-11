#include "lockableiconbutton.hpp"

#include <QStyle>

LockableIconButton::LockableIconButton(QWidget *parent)
    : IconButton(parent)
    , m_locked(false)
{
    connect(this, &LockableIconButton::clicked, this, &LockableIconButton::onClicked);
}

void LockableIconButton::setLocked(bool locked)
{
    m_locked = locked;

    style()->unpolish(this);
    style()->polish(this);

    emit this->locked(locked);
}

bool LockableIconButton::isLocked() const
{
    return m_locked;
}

void LockableIconButton::onClicked()
{
    setLocked(!m_locked);
}
