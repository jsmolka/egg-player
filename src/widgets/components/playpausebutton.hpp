#ifndef PLAYPAUSEBUTTON_HPP
#define PLAYPAUSEBUTTON_HPP

#include "iconbutton.hpp"

class PlayPauseButton : public IconButton
{
public:
    enum Icon {Play, Pause};

    explicit PlayPauseButton(QWidget *parent = nullptr);

    void setIcon(PlayPauseButton::Icon icon);
    PlayPauseButton::Icon icon() const;

private slots:
    void updateIcon();

private:
    PlayPauseButton::Icon m_icon;
};

#endif // PLAYPAUSEBUTTON_HPP
