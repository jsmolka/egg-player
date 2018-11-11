#ifndef PLAYPAUSEBUTTON_HPP
#define PLAYPAUSEBUTTON_HPP

#include "widgets/iconbutton.hpp"

class PlayPauseButton : public IconButton
{
public:
    enum Icon {Play, Pause};

    explicit PlayPauseButton(QWidget *parent = nullptr);

    void setIcon(Icon icon);
    Icon icon() const;

private slots:
    void updateIcon();

private:
    Icon m_icon;
};

#endif // PLAYPAUSEBUTTON_HPP
