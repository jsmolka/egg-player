#include "mainwindow.hpp"

MainWindow::MainWindow() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");

    setupUi();
}

void MainWindow::play()
{
    Player *player = pm_playerWindow->player();
    IconButton *playButton = pm_playerWindow->playButton();

    if (player->currentIndex() != -1)
    {
        playButton->switchIcon();

        if (!playButton->isSelected())
            player->play();
        else
            player->pause();
    }
}

void MainWindow::start(const QModelIndex &index)
{
    Player *player = pm_playerWindow->player();
    IconButton *playButton = pm_playerWindow->playButton();

    player->setAudioList(m_library.audioList());

    updateTrackInfo(index.row());
    playButton->setSelected(0);

    player->setCurrentIndex(index.row());
    player->play();
}

void MainWindow::next()
{
    Player *player = pm_playerWindow->player();
    int index = player->nextIndex();
    if (index != -1)
    {
        updateTrackInfo(index);

        player->setCurrentIndex(index);
    }
}

void MainWindow::back()
{
    Player *player = pm_playerWindow->player();
    int index = player->backIndex();
    if (index != -1)
    {
        updateTrackInfo(index);

        player->setCurrentIndex(index);
    }
}

void MainWindow::loop()
{
    Player *player = pm_playerWindow->player();
    IconButton *replayButton = pm_playerWindow->replayButton();

    if (replayButton->isLocked())
        player->setLoop(true);
    else
        player->setLoop(false);
}

void MainWindow::setupUi()
{
    createMusicWindow();
    createPlayerWindow();

    QLabel *west = new QLabel;
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0);
    layout->addWidget(pm_musicWindow, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(pm_playerWindow, BorderLayout::South);
    setLayout(layout);
}

void MainWindow::updateTrackInfo(int index)
{
    Player *player = pm_playerWindow->player();
    QLabel *trackLabel = pm_playerWindow->trackLabel();
    QLabel *coverLabel = pm_playerWindow->coverLabel();

    QString title = player->titleAt(index);
    QString artist = player->artistAt(index);
    QPixmap cover = player->coverAt(index);

    trackLabel->setText(QString("%1\n%2").arg(title, artist));
    coverLabel->setPixmap(cover);
}

void MainWindow::createMusicWindow()
{
    pm_musicWindow = new MusicWindow(&m_library);

    connect(pm_musicWindow, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(start(QModelIndex)));
}

void MainWindow::createPlayerWindow()
{
    pm_playerWindow = new PlayerWindow;

    Player *player = pm_playerWindow->player();
    player->setVolume(5);

    connect(pm_playerWindow->playButton(), SIGNAL(pressed()), this, SLOT(play()));
    connect(pm_playerWindow->nextButton(), SIGNAL(pressed()), this, SLOT(next()));
    connect(pm_playerWindow->backButton(), SIGNAL(pressed()), this, SLOT(back()));
    connect(pm_playerWindow->replayButton(), SIGNAL(locked()), this, SLOT(loop()));
}
