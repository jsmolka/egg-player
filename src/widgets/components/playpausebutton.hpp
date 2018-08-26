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

private slots:
    void updateIcon();

private:
    PlayPauseButton::Icon m_icon;
};

#endif // PLAYPAUSEBUTTON_HPP
