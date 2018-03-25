#include "mainwindow.hpp"

MainWindow::MainWindow() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");

    setupUi();
}

void MainWindow::play()
{
    Player *player = pm_playerWindow->player();
    IconButton *button = pm_playerWindow->playButton();

    if (button->selected())
        player->play();
    else
        player->pause();
}

void MainWindow::play(const QModelIndex &index)
{
    Player *player = pm_playerWindow->player();

    QLabel *cover = pm_playerWindow->coverLabel();
    cover->setPixmap(m_library.at(index.row()).pixmap(50));

    player->setAudioList(m_library.audioList());
    player->setIndex(index.row());
    qDebug() << player->currentAudio().title();
    player->play();

    // Set play button to correct state
    pm_playerWindow->playButton()->setSelected(false);
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

void MainWindow::createMusicWindow()
{
    pm_musicWindow = new MusicWindow(&m_library);

    connect(pm_musicWindow, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(play(QModelIndex)));
}

void MainWindow::createPlayerWindow()
{
    pm_playerWindow = new PlayerWindow;

    Player *player = pm_playerWindow->player();
    player->setIndex(0);
    player->setVolume(5);

    connect(pm_playerWindow->playButton(), SIGNAL(pressed()), this, SLOT(play()));
}
