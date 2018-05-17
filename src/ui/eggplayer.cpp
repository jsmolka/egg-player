#include "eggplayer.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
EggPlayer::EggPlayer(QWidget *parent) :
    QWidget(parent),
    m_library(this),
    m_musicLibrary(this),
    m_musicBar(this)
{
    setupUi();

    connect(&m_library, SIGNAL(inserted(Audio*, int)), &m_musicLibrary, SLOT(insert(Audio*, int)));
    connect(&m_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onMusicLibraryDoubleClicked(QModelIndex)));

    m_library.setSorted(true);
    m_library.load(Config::Library::paths());
}

/*
 * Destructor.
 */
EggPlayer::~EggPlayer()
{

}

/*
 * Loads the saved registry position and shows
 * the window. Should be called instead of show().
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
 * Musc library double clicked event. It starts
 * the player with the clicked audio.
 *
 * :param index: index
 */
void EggPlayer::onMusicLibraryDoubleClicked(const QModelIndex &index)
{
    m_musicBar.player()->loadPlaylist(m_library.audios(), index.row());
    m_musicBar.player()->play();
}

/*
 * Sets up user interface.
 */
void EggPlayer::setupUi()
{
    QLabel *west = new QLabel(this);
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    m_musicLibrary.showColumn(MusicLibrary::Title);
    m_musicLibrary.showColumn(MusicLibrary::Artist);
    m_musicLibrary.showColumn(MusicLibrary::Album);
    m_musicLibrary.showColumn(MusicLibrary::Year, Qt::AlignLeft, false);
    m_musicLibrary.showColumn(MusicLibrary::Genre);
    m_musicLibrary.showColumn(MusicLibrary::Length, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(&m_musicBar, BorderLayout::South);
    setLayout(layout);
}

/*
 * Saves current position in registry. Does not
 * need to be in config because position is not
 * really relevant there.
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
