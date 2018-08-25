#ifndef BARWIDGET_HPP
#define BARWIDGET_HPP

#include <QLabel>

#include "audio.hpp"
#include "colortransitionwidget.hpp"
#include "iconbutton.hpp"
#include "playpausebutton.hpp"
#include "slider.hpp"
#include "shortcut.hpp"
#include "volumebutton.hpp"

class BarWidget : public ColorTransitionWidget
{
    Q_OBJECT

public:
    explicit BarWidget(QWidget *parent = nullptr);

    QLabel &coverLabel();
    QLabel &trackLabel();
    QLabel &currentTimeLabel();
    QLabel &totalTimeLabel();

    IconButton &playPauseButton();
    IconButton &nextButton();
    IconButton &previousButton();
    IconButton &shuffleButton();
    IconButton &loopButton();
    IconButton &volumeButton();

    Slider &lengthSlider();
    Slider &volumeSlider();

private slots:
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerStateChanged();
    void onPlayerPositionChanged(int position);
    void onPlayerVolumeChanged(int volume);
    void onPlayPauseButtonPressed();
    void onVolumeButtonPressed();
    void onLengthSliderMoved(int value);
    void onLengthSliderValueChanged(int value);
    void onVolumeSliderMoved(int value);
    void onShortcutPlayPausePressed();
    void onShortcutVolumeUpPressed();
    void onShortcutVolumeDownPressed();

private:
    void setup();
    void setupCss();
    void setupUi();

    QLabel m_coverLabel;
    QLabel m_trackLabel;
    QLabel m_currentTimeLabel;
    QLabel m_totalTimeLabel;

    PlayPauseButton m_playPauseButton;
    IconButton m_nextButton;
    IconButton m_previousButton;
    IconButton m_shuffleButton;
    IconButton m_loopButton;
    VolumeButton m_volumeButton;

    Slider m_lengthSlider;
    Slider m_volumeSlider;

    Shortcut m_scPlayPause;
    Shortcut m_scNext;
    Shortcut m_scPrevious;
    Shortcut m_scVolumeUp;
    Shortcut m_scVolumeDown;
};

#endif // BARWIDGET_HPP
