#ifndef MUSICBAR_HPP
#define MUSICBAR_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>

#include "cache.hpp"
#include "colorutil.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "fileutil.hpp"
#include "iconbutton.hpp"
#include "lengthslider.hpp"
#include "player.hpp"
#include "util.hpp"

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
    IconButton * nextButton();
    IconButton * playButton();
    IconButton * backButton();
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
    void onLengthSliderMoved(int position);
    void onLengthSliderPositionChanged(int position);

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
    IconButton *pm_nextButton;
    IconButton *pm_playButton;
    IconButton *pm_backButton;
    IconButton *pm_shuffleButton;
    IconButton *pm_loopButton;
    IconButton *pm_volumeButton;
};

#endif // MUSICBAR_HPP
