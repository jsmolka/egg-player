#include "eggplayer.hpp"

/*
 * Constructor.
 */
EggPlayer::EggPlayer()
{
    pm_library = new Library(Config::LPath());
    pm_library->sortByTitle();

    setupUi();

    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onMusicLibraryDoubleClicked(QModelIndex)));
}

/*
 * Destructor.
 */
EggPlayer::~EggPlayer()
{
    delete pm_library;
}

/*
 * Loads the saved registry position and
 * shows the window. Should be called
 * instead of show().
 */
void EggPlayer::showSavedPosition()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());

    if (settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    else
        show();
}

/*
 * Implemented close event to save current
 * position before closing.
 *
 * :param event: event
 */
void EggPlayer::closeEvent(QCloseEvent *event)
{
    savePosition();
    QWidget::closeEvent(event);
}

/*
 * Slot for MusicLibrary double clicked event.
 * It starts the player with the clicked audio.
 *
 * :param index: music library index
 */
void EggPlayer::onMusicLibraryDoubleClicked(const QModelIndex &index)
{
    Player *player = pm_musicBar->player();
    IconButton *shuffleButton = pm_musicBar->shuffleButton();

    player->setPlaylist(pm_library->audioList());
    player->setIndex(index.row());
    player->setShuffled(shuffleButton->isLocked());
    player->play();
}

/*
 * Sets up user interface.
 */
void EggPlayer::setupUi()
{
    pm_musicLibrary = new MusicLibrary(pm_library, this);
    pm_musicBar = new MusicBar(this);

    QLabel *west = new QLabel(this);
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(pm_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(pm_musicBar, BorderLayout::South);
    setLayout(layout);
}

/*
 * Saves current position in registry. Does
 * not need to be in config because position
 * is not really relevant there.
 */
void EggPlayer::savePosition()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("maximized", isMaximized());
    if (!isMaximized())
    {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }
}
