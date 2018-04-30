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
#include "lengthslider.hpp"
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
    LengthSlider * lengthSlider();
    IconButton * playButton();
    IconButton * nextButton();
    IconButton * previousButton();
    IconButton * shuffleButton();
    IconButton * loopButton();
    IconButton * volumeButton();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void onPlayButtonPressed();
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerStateChanged(Player::State state);
    void onPlayerPositionChanged(int position);
    void onPlayerVolumeChanged(int volume);
    void onShuffleButtonLocked(bool locked);
    void onLoopButtonLocked(bool locked);
    void onLengthSliderMoved(int position);
    void onLengthSliderPositionChanged(int position);
    void onShortcutPlayPausePressed();
    void onShortcutVolumeUpPressed();
    void onShortcutVolumeDownPressed();

private:
    void setupUi();
    QPixmap defaultCover();
    void setColor(const QColor &color);

    Player *pm_player;
    QLabel *pm_coverLabel;
    QLabel *pm_trackLabel;
    QLabel *pm_currentTimeLabel;
    QLabel *pm_totalTimeLabel;
    LengthSlider *pm_lengthSlider;
    IconButton *pm_playButton;
    IconButton *pm_nextButton;
    IconButton *pm_previousButton;
    IconButton *pm_shuffleButton;
    IconButton *pm_loopButton;
    IconButton *pm_volumeButton;
    Shortcut *pm_scPlayPause;
    Shortcut *pm_scNext;
    Shortcut *pm_scPrevious;
    Shortcut *pm_scVolumeUp;
    Shortcut *pm_scVolumeDown;
};

#endif // MUSICBAR_HPP
