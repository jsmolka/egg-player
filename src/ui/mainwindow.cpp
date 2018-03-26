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

    playButton->switchIcon();

    if (!playButton->isSelected())
        player->play();
    else
        player->pause();
}

void MainWindow::start(const QModelIndex &index)
{
    Player *player = pm_playerWindow->player();
    IconButton *playButton = pm_playerWindow->playButton();

    player->setAudioList(m_library.audioList());
    player->setCurrentIndex(index.row());
    player->play();

    playButton->setSelected(0);

    updateTrackInfo();
}

void MainWindow::next()
{
    Player *player = pm_playerWindow->player();
    int index = player->nextIndex();
    if (index != -1)
    {
        player->setCurrentIndex(index);

        updateTrackInfo();
    }
}

void MainWindow::back()
{
    Player *player = pm_playerWindow->player();
    int index = player->backIndex();
    if (index != -1)
    {
        player->setCurrentIndex(index);

        updateTrackInfo();
    }
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

void MainWindow::updateTrackInfo()
{
    Player *player = pm_playerWindow->player();
    QLabel *trackLabel = pm_playerWindow->trackLabel();
    QLabel *coverLabel = pm_playerWindow->coverLabel();

    trackLabel->setText(QString("%1\n%2").arg(player->currentTitle(), player->currentArtist()));
    //coverLabel->setPixmap(player->currentCover());
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
}
