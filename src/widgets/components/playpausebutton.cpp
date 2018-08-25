#include "playpausebutton.hpp"

#include "constants.hpp"
#include "iconfactory.hpp"

PlayPauseButton::PlayPauseButton(QWidget *parent)
    : IconButton(parent)
    , m_icon(Play)
{
    setIcons({
        IconFactory::make(ICO_PLAY),
        IconFactory::make(ICO_PAUSE)
    });

    setIcon(m_icon);
}

void PlayPauseButton::setIcon(Icon icon)
{
    m_icon = icon;

    switch (icon)
    {
    case Play:
        return setIconIndex(0);
    case Pause:
        return setIconIndex(1);
    }
}

PlayPauseButton::Icon PlayPauseButton::icon() const
{
    return m_icon;
}
