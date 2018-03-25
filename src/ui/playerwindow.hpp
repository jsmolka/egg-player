#ifndef PLAYERWINDOW_HPP
#define PLAYERWINDOW_HPP

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QStyleOption>
#include <QWidget>

#include "src/constants/path.hpp"
#include "src/core/player.hpp"
#include "src/ui/components/iconbutton.hpp"
#include "src/utils/fileutil.hpp"

class PlayerWindow : public QWidget
{
    Q_OBJECT

public:
    PlayerWindow();

    Player * player();
    QLabel *coverLabel();
    QLabel *trackLabel();
    IconButton * nextButton();
    IconButton * playButton();
    IconButton * backButton();
    IconButton * shuffleButton();
    IconButton * replayButton();
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
    IconButton *pm_replayButton;
    IconButton *pm_volumeButton;

};

#endif // PLAYERWINDOW_HPP
