#ifndef MUSICBAR_HPP
#define MUSICBAR_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>

#include "cache.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "iconbutton.hpp"
#include "clickableslider.hpp"
#include "player.hpp"
#include "shortcut.hpp"
#include "utils.hpp"

class MusicBar : public QWidget
{
    Q_OBJECT

public:
    MusicBar(QWidget *parent = nullptr);
    ~MusicBar();

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

    ClickableSlider * lengthSlider();
    ClickableSlider * volumeSlider();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerStateChanged(Player::State state);
    void onPlayerPositionChanged(int position);
    void onPlayerVolumeChanged(int volume);

    void onPlayPauseButtonPressed();
    void onShuffleButtonLocked(bool locked);
    void onLoopButtonLocked(bool locked);
    void onVolumeButtonPressed();

    void onLengthSliderMoved(int value);
    void onLengthSliderValueChanged(int value);
    void onVolumeSliderMoved(int value);
    void onVolumeSliderValueChanged(int value);

    void onShortcutPlayPausePressed();
    void onShortcutVolumeUpPressed();
    void onShortcutVolumeDownPressed();

private:
    void loadCss();
    void setup();
    void setupUi();

    void setColor(const QColor &color);

    void setButtonVisibility(bool visible);
    void hideButtons();
    void showButtons();

    void setVolumeConfig(int volume);
    void setVolumeIcon(int volume);
    void setVolumePlayer(int volume);
    void setVolumeSlider(int volume);
    void changeVolume(int volume, int step);

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

    ClickableSlider m_lengthSlider;
    ClickableSlider m_volumeSlider;

    Shortcut m_scPlayPause;
    Shortcut m_scNext;
    Shortcut m_scPrevious;
    Shortcut m_scVolumeUp;
    Shortcut m_scVolumeDown;
};

#endif // MUSICBAR_HPP
