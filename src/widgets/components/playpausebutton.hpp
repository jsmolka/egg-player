#ifndef PLAYPAUSEBUTTON_HPP
#define PLAYPAUSEBUTTON_HPP

#include "iconbutton.hpp"

class PlayPauseButton : public IconButton
{
public:
    explicit PlayPauseButton(QWidget *parent = nullptr);

    enum Icon {Play, Pause};

    void setIcon(PlayPauseButton::Icon icon);
    PlayPauseButton::Icon icon() const;

private:
    Icon m_icon;
};

#endif // PLAYPAUSEBUTTON_HPP
