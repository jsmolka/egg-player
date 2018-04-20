#include "iconbutton.hpp"

/*
 * Constructor.
 *
 * :param parent: parent object
 */
IconButton::IconButton(QWidget *parent) : QPushButton(parent)
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
 * Icons setter.
 *
 * :param icons: list of icons
 */
void IconButton::setIcons(const QList<QIcon> &icons)
{
    m_icons = icons;
}

/*
 * Icons getter.
 *
 * :return: list of icons
 */
QList<QIcon> IconButton::icons() const
{
    return m_icons;
}

/*
 * Changes icon based on index.
 *
 * :param index: index
 */
void IconButton::setSelectedIcon(int index)
{
    m_index = index;

    setIcon(m_icons[index]);
}

/*
 * Returns selected index.
 *
 * :return: index
 */
int IconButton::selectedIcon() const
{
    return m_index;
}

/*
 * Setter for locked property.
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
 * :return: is locked
 */
bool IconButton::isLocked() const
{
    return m_locked;
}

/*
 * Make button lockable.
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
 * Initialize function for button.
 *
 * :param icons: list of possible icons
 * :param size: icon size
 * :param lockable: is lockable
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
 * Slot for clicked event. If the button
 * is lockable the property get switched
 * and the stylesheet gets reloaded.
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
