#ifndef MUSICBAR_HPP
#define MUSICBAR_HPP

#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QStyleOption>
#include <QWidget>

#include "src/constants/constant.hpp"
#include "src/core/player.hpp"
#include "src/ui/components/iconbutton.hpp"

class MusicBar : public QWidget
{
    Q_OBJECT

public:
    MusicBar();

    Player * player();
    QLabel * coverLabel();
    QLabel * trackLabel();
    IconButton * nextButton();
    IconButton * playButton();
    IconButton * backButton();
    IconButton * shuffleButton();
    IconButton * loopButton();
    IconButton * volumeButton();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void setupUi();
    QPixmap defaultCover();

    Player *pm_player;
    QLabel *pm_coverLabel;
    QLabel *pm_trackLabel;
    IconButton *pm_nextButton;
    IconButton *pm_playButton;
    IconButton *pm_backButton;
    IconButton *pm_shuffleButton;
    IconButton *pm_loopButton;
    IconButton *pm_volumeButton;
};

#endif // MUSICBAR_HPP
