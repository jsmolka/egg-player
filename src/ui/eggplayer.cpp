#include "eggplayer.hpp"

EggPlayer::EggPlayer(QWidget *parent) : QWidget(parent)
{
    m_library = Library("D:/Backup/Compressed Music");

    setupUi();

    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onLibraryDoubleClicked(QModelIndex)));
}

EggPlayer::~EggPlayer()
{

}

void EggPlayer::onLibraryDoubleClicked(const QModelIndex &index)
{
    Player *player = pm_musicBar->player();
    IconButton *shuffleButton = pm_musicBar->shuffleButton();

    player->setAudioList(m_library.audioList());
    player->setIndex(index.row());
    player->setShuffled(shuffleButton->isLocked());
    player->play();
}

void EggPlayer::setupUi()
{
    createMusicLibrary();
    createMusicBar();

    QLabel *west = new QLabel;
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0);
    layout->addWidget(pm_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(pm_musicBar, BorderLayout::South);
    setLayout(layout);
}

void EggPlayer::createMusicLibrary()
{
    pm_musicLibrary = new MusicLibrary(&m_library, this);
}

void EggPlayer::createMusicBar()
{
    pm_musicBar = new MusicBar(this);

    Player *player = pm_musicBar->player();
    player->setVolume(5);
}
