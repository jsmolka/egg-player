#ifndef MUSICBAR_HPP
#define MUSICBAR_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>

#include "src/constants/constant.hpp"
#include "src/core/cache.hpp"
#include "src/core/player.hpp"
#include "src/ui/components/iconbutton.hpp"
#include "src/ui/components/lengthslider.hpp"
#include "src/utils/colorutil.hpp"

class MusicBar : public QWidget
{
    Q_OBJECT

public:
    MusicBar(QWidget *parent = 0);
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
    void paintEvent(QPaintEvent *event);

private slots:
    void onPlayButtonPressed();
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerStateChanged(bool playing);
    void onPlayerPositionChanged(int position);

private:
    void setupUi();
    QPixmap defaultCover();
    QString lengthString(int length);
    void setColor(const QColor &color);

    Cache m_cache;
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
