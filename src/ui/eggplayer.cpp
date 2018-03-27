#include "eggplayer.hpp"

EggPlayer::EggPlayer() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");
    m_cache.connect();

    setupUi();
}

void EggPlayer::play()
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();

    if (player->currentIndex() != -1)
    {
        playButton->switchIcon();

        if (!playButton->isSelected())
            player->play();
        else
            player->pause();
    }
}

void EggPlayer::start(const QModelIndex &index)
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();

    player->setAudioList(m_library.audioList());
    player->setCurrentIndex(index.row());
    player->play();

    playButton->setSelected(1);
}

void EggPlayer::next()
{
    Player *player = pm_musicBar->player();

    int index = player->nextIndex();
    if (index != -1)
        player->setCurrentIndex(index);
}

void EggPlayer::back()
{
    Player *player = pm_musicBar->player();

    int index = player->backIndex();
    if (index != -1)
        player->setCurrentIndex(index);
}

void EggPlayer::loop()
{
    Player *player = pm_musicBar->player();
    IconButton *replayButton = pm_musicBar->loopButton();

    if (replayButton->isLocked())
        player->setLoop(true);
    else
        player->setLoop(false);
}

void EggPlayer::change()
{
    Player *player = pm_musicBar->player();

    if (player->currentIndex() != -1)
        updateTrackInfo();
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

void EggPlayer::updateTrackInfo()
{
    Audio *audio = pm_musicBar->player()->currentAudio();
    QLabel *trackLabel = pm_musicBar->trackLabel();
    QLabel *coverLabel = pm_musicBar->coverLabel();

    QString title = audio->title();
    QString artist = audio->artist();
    QString album = audio->album();
    QPixmap cover = m_cache.cover(artist, album, 50);

    trackLabel->setText(QString("%1\n%2").arg(title, artist));
    coverLabel->setPixmap(cover);
}

void EggPlayer::createMusicLibrary()
{
    pm_musicLibrary = new MusicLibrary(&m_library);

    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(start(QModelIndex)));
}

void EggPlayer::createMusicBar()
{
    pm_musicBar = new MusicBar;

    Player *player = pm_musicBar->player();
    player->setVolume(5);

    connect(pm_musicBar->playButton(), SIGNAL(pressed()), this, SLOT(play()));
    connect(pm_musicBar->nextButton(), SIGNAL(pressed()), this, SLOT(next()));
    connect(pm_musicBar->backButton(), SIGNAL(pressed()), this, SLOT(back()));
    connect(pm_musicBar->loopButton(), SIGNAL(locked()), this, SLOT(loop()));

    connect(pm_musicBar->player(), SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(change()));
}
