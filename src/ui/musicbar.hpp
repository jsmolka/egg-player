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

    Player * player();

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

    void onPlayButtonPressed();
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
    enum Positions
    {
        CoverLabelPosition = 0,
        TrackLabelPosition = 1,
        CurrentTimeLabelPosition = 2,
        LengthSliderPosition = 3,
        TotalTimeLabelPosition = 4,
        PreviousButtonPosition = 5,
        PlayPauseButtonPosition = 6,
        NextButtonPosition = 7,
        ShuffleButtonPosition = 8,
        LoopButtonPosition = 9,
        VolumeButtonPosition = 10
    };

    void setupUi();
    void createAudioInfo();
    void createLengthSlider();
    void createButtons();

    void setColor(const QColor &color);

    void setVolumePlayer(int volume);
    void setVolumeIcon(int volume);
    void setVolumeConfig(int volume);

    Player *pm_player;

    QLabel *pm_coverLabel;
    QLabel *pm_trackLabel;
    QLabel *pm_currentTimeLabel;
    QLabel *pm_totalTimeLabel;

    IconButton *pm_playPauseButton;
    IconButton *pm_nextButton;
    IconButton *pm_previousButton;
    IconButton *pm_shuffleButton;
    IconButton *pm_loopButton;
    IconButton *pm_volumeButton;

    ClickableSlider *pm_lengthSlider;
    ClickableSlider *pm_volumeSlider;

    Shortcut *pm_scPlayPause;
    Shortcut *pm_scNext;
    Shortcut *pm_scPrevious;
    Shortcut *pm_scVolumeUp;
    Shortcut *pm_scVolumeDown;
};

#endif // MUSICBAR_HPP
