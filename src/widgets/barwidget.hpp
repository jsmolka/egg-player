#ifndef BARWIDGET_HPP
#define BARWIDGET_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>

#include "cache.hpp"
#include "colortransitionwidget.hpp"
#include "colorutil.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "iconbutton.hpp"
#include "slider.hpp"
#include "player.hpp"
#include "shortcut.hpp"

class BarWidget : public ColorTransitionWidget
{
    Q_OBJECT

public:
    BarWidget(QWidget *parent = nullptr);
    ~BarWidget();

    QLabel * coverLabel();
    QLabel * trackLabel();
    QLabel * currentTimeLabel();
    QLabel * totalTimeLabel();

    IconButton * playPauseButton();
    IconButton * nextButton();
    IconButton * previousButton();
    IconButton * shuffleButton();
    IconButton * loopButton();
    IconButton * volumeButton();

    Slider * lengthSlider();
    Slider * volumeSlider();

private slots:
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerStateChanged();
    void onPlayerPositionChanged(int position);
    void onPlayerVolumeChanged(int volume);
    void onPlayPauseButtonPressed();
    void onShuffleButtonLocked(bool locked);
    void onLoopButtonLocked(bool locked);
    void onVolumeButtonPressed();
    void onLengthSliderMoved(int value);
    void onLengthSliderValueChanged(int value);
    void onVolumeSliderMoved(int value);
    void onShortcutPlayPausePressed();
    void onShortcutVolumeUpPressed();
    void onShortcutVolumeDownPressed();

private:
    void setup();
    void setupUi();

    void setButtonVisibility(bool visible);

    void setVolumeConfig(int volume);
    void setVolumeIcon(int volume);
    void setVolumePlayer(int volume);
    void setVolumeSlider(int volume);

    QLabel m_coverLabel;
    QLabel m_trackLabel;
    QLabel m_currentTimeLabel;
    QLabel m_totalTimeLabel;

    IconButton m_playPauseButton;
    IconButton m_nextButton;
    IconButton m_previousButton;
    IconButton m_shuffleButton;
    IconButton m_loopButton;
    IconButton m_volumeButton;

    Slider m_lengthSlider;
    Slider m_volumeSlider;

    Shortcut m_scPlayPause;
    Shortcut m_scNext;
    Shortcut m_scPrevious;
    Shortcut m_scVolumeUp;
    Shortcut m_scVolumeDown;
};

#endif // BARWIDGET_HPP
