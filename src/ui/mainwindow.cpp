#include "mainwindow.hpp"

MainWindow::MainWindow() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");

    setupUi();
}

void MainWindow::play()
{
    Player *player = pm_playerWindow->player();

    if (pm_playerWindow->playButton()->selected())
        player->play();
    else
        player->pause();
}

void MainWindow::start(const QModelIndex &index)
{
    // Set current song information
    updateInfo(m_library.at(index.row()));

    // Set play button to correct state
    pm_playerWindow->playButton()->setSelected(false);

    // Setup player
    Player *player = pm_playerWindow->player();
    player->setAudioList(m_library.audioList());
    player->setIndex(index.row());
    player->play();
}

void MainWindow::next()
{
    // Get next index
    Player *player = pm_playerWindow->player();
    int current = player->index();
    int count = player->playlist()->mediaCount() - 1;
    if (current == count)
        current = 0;
    else
        current++;

    // Set current song information
    updateInfo(m_library.at(current));

    // Setup player
    player->setIndex(current);
}

void MainWindow::back()
{
    // Get next index
    Player *player = pm_playerWindow->player();
    int current = player->index();
    int count = player->playlist()->mediaCount() - 1;
    if (current == 0)
        count;
    else
        current--;

    // Set current song information
    updateInfo(m_library.at(current));

    // Setup player
    player->setIndex(current);
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

void MainWindow::updateInfo(Audio *audio)
{
    QLabel *cover = pm_playerWindow->coverLabel();
    cover->setPixmap(audio->pixmap(50));
    QLabel *track = pm_playerWindow->trackLabel();
    track->setText(QString("%1\n%2").arg(audio->title(), audio->artist()));
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
    player->setIndex(0);
    player->setVolume(5);

    connect(pm_playerWindow->playButton(), SIGNAL(pressed()), this, SLOT(play()));
    connect(pm_playerWindow->nextButton(), SIGNAL(pressed()), this, SLOT(next()));
    connect(pm_playerWindow->backButton(), SIGNAL(pressed()), this, SLOT(back()));
}
