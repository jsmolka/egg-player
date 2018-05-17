#include "iconbutton.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, defaut nullptr
 */
IconButton::IconButton(QWidget *parent) :
    QPushButton(parent),
    m_index(true),
    m_lockable(false),
    m_locked(false)
{
    setup();

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
void IconButton::setIcons(const QVector<QIcon> &icons)
{
    m_icons = icons;
}

/*
 * Getter for icons property.
 *
 * :return: list of icons
 */
QVector<QIcon> IconButton::icons() const
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
 * Setter for locked property. Reloads the
 * buttons stylesheet.
 *
 * :param locked: locked
 * :emit locked: locked
 */
void IconButton::setLocked(bool locked)
{
    m_locked = locked;

    if (!m_lockable)
        return;

    style()->unpolish(this);
    style()->polish(this);
    emit this->locked(m_locked);
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
 * is lockable it will update based on the locked
 * property if it gets clicked.
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
 * :param icons: icon paths
 * :param size: icon size
 * :param lockable: is lockable, default false
 */
void IconButton::init(const QStringList &icons, int size, bool lockable)
{
    m_lockable = lockable;
    m_icons.clear();
    for (const QString &icon : icons)
        m_icons << QPixmap(icon);

    setIcon(m_icons.first());
    setIconSize(QSize(size, size));
    setFixedSize(QSize(size, size));
}

/*
 * Clicked event. Switches the locked
 * property.
 */
void IconButton::onClicked()
{
    setLocked(!m_locked);
}

/*
 * Sets up widget.
 */
void IconButton::setup()
{
    setFocusPolicy(Qt::NoFocus);
}
