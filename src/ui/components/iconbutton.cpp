#include "iconbutton.hpp"

/*
 * Constructor.
 *
 * :param parent: parent
 */
IconButton::IconButton(QWidget *parent) :
    QPushButton(parent)
{
    m_index = true;
    m_lockable = false;
    m_locked = false;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

/*
 * Destructor.
 */
IconButton::~IconButton()
{

}

/*
 * Setter for icons property.
 *
 * :param icons: list of icons
 */
void IconButton::setIcons(const QList<QIcon> &icons)
{
    m_icons = icons;
}

/*
 * Getter for icons property.
 *
 * :return: list of icons
 */
QList<QIcon> IconButton::icons() const
{
    return m_icons;
}

/*
 * Setter for index property.
 *
 * :param index: index
 */
void IconButton::setSelectedIcon(int index)
{
    m_index = index;
    setIcon(m_icons[index]);
}

/*
 * Getter for index property.
 *
 * :return: index
 */
int IconButton::selectedIcon() const
{
    return m_index;
}

/*
 * Setter for locked property. Locking button
 * will only take effect if the button is lockable.
 *
 * :param locked: locked
 */
void IconButton::setLocked(bool locked)
{
    m_locked = locked;
}

/*
 * Getter for locked property.
 *
 * :return: locked
 */
bool IconButton::isLocked() const
{
    return m_locked;
}

/*
 * Setter for lockable property. If the button
 * is lockable it will update based on the
 * locked property if it gets clicked.
 *
 * :param lockable: lockable
 */
void IconButton::setLockable(bool lockable)
{
    m_lockable = lockable;
}

/*
 * Getter for lockable property.
 *
 * :return: is lockable
 */
bool IconButton::isLockable() const
{
    return m_lockable;
}

/*
 * Initialize function for button. It sets the
 * button icon to the first item in icons and
 * resizes it.
 *
 * :param icons: list of icons
 * :param size: icon size
 * :param lockable: is lockable, default false
 */
void IconButton::init(const QList<QIcon> &icons, int size, bool lockable)
{
    m_icons = icons;
    m_lockable = lockable;

    QSize iconSize = QSize(size, size);

    setIcon(icons[0]);
    setIconSize(iconSize);
    setFixedSize(iconSize);
}

/*
 * Slot for clicked event. If the button is
 * lockable the locked property get switched
 * and the style sheet gets reloaded.
 */
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
