#ifndef PLAYERWINDOW_HPP
#define PLAYERWINDOW_HPP

#include <QGridLayout>
#include <QList>
#include <QWidget>

#include <QStyleOption>
#include <QPainter>

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
    IconButton * playButton();
    IconButton * nextButton();
    IconButton * backButton();
    IconButton * shuffleButton();
    IconButton * replayButton();
    IconButton * volumeButton();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void setupUi();

    Player *pm_player;
    IconButton *pm_playButton;
    IconButton *pm_nextButton;
    IconButton *pm_backButton;
    IconButton *pm_shuffleButton;
    IconButton *pm_replayButton;
    IconButton *pm_volumeButton;

};

#endif // PLAYERWINDOW_HPP
