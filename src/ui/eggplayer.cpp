#include "eggplayer.hpp"

EggPlayer::EggPlayer(QWidget *parent) : QWidget(parent)
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");
    m_cache.connect();

    setupUi();
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

    if (shuffleButton->isLocked())
        player->shuffle();

    player->play();
}

void EggPlayer::onPlayButtonPressed()
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();

    if (player->index() != -1)
    {
        if (playButton->selectedIcon() == 0)
            player->play();
        else
            player->pause();
    }
}

void EggPlayer::onLoopButtonLocked(bool locked)
{
    Player *player = pm_musicBar->player();

    player->setLoop(locked);
}

void EggPlayer::onShuffleButtonLocked(bool locked)
{
    Player *player = pm_musicBar->player();

    if (player->index() != -1)
    {
        if (locked)
            player->shuffle();
        else
            player->unshuffle();
    }
}

void EggPlayer::onPlayerAudioChanged(Audio *audio)
{
    updateTrackInfo(audio);
}

void EggPlayer::onPlayerStateChanged(bool playing)
{
    IconButton *playButton = pm_musicBar->playButton();

    playButton->setSelectedIcon(playing ? 1 : 0);
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

void EggPlayer::updateTrackInfo(Audio *audio)
{
    QLabel *trackLabel = pm_musicBar->trackLabel();
    QLabel *coverLabel = pm_musicBar->coverLabel();

    QString path = audio->path();
    QString title = audio->title();
    QString artist = audio->artist();
    QPixmap cover = m_cache.cover(path, 50);

    trackLabel->setText(QString("%1\n%2").arg(title, artist));
    coverLabel->setPixmap(cover);
}

void EggPlayer::createMusicLibrary()
{
    pm_musicLibrary = new MusicLibrary(&m_library, this);

    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onLibraryDoubleClicked(QModelIndex)));
}

void EggPlayer::createMusicBar()
{
    pm_musicBar = new MusicBar(this);

    Player *player = pm_musicBar->player();
    player->setVolume(5);

    connect(pm_musicBar->playButton(), SIGNAL(pressed()), this, SLOT(onPlayButtonPressed()));
    connect(pm_musicBar->loopButton(), SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(pm_musicBar->shuffleButton(), SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));

    connect(pm_musicBar->nextButton(), SIGNAL(pressed()), pm_musicBar->player(), SLOT(next()));
    connect(pm_musicBar->backButton(), SIGNAL(pressed()), pm_musicBar->player(), SLOT(back()));

    connect(pm_musicBar->player(), SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(pm_musicBar->player(), SIGNAL(stateChanged(bool)), this, SLOT(onPlayerStateChanged(bool)));
}
