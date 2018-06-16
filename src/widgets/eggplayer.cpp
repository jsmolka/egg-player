#include "eggplayer.hpp"

EggPlayer::EggPlayer(QWidget *parent)
    : QWidget(parent)
    , m_library(true, this)
    , m_musicLibrary(this)
    , m_musicBar(this)
{
    eggPlayer->setVolume(cfgPlayer->volume());
    eggPlayer->setShuffle(cfgPlayer->shuffle());
    eggPlayer->setLoop(cfgPlayer->loop());

    setupUi();

    connect(&m_library, SIGNAL(inserted(Audio *, int)), &m_musicLibrary, SLOT(insert(Audio *, int)));
    connect(&m_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onMusicLibraryDoubleClicked(QModelIndex)));

    m_library.load(cfgLibrary->paths());
}

EggPlayer::~EggPlayer()
{

}

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

void EggPlayer::closeEvent(QCloseEvent *event)
{
    savePosition();
    QWidget::closeEvent(event);
}

void EggPlayer::onMusicLibraryDoubleClicked(const QModelIndex &index)
{
    eggPlayer->loadPlaylist(m_library.audios(), index.row());
    eggPlayer->play();
}

void EggPlayer::setupUi()
{
    QLabel *west = new QLabel(this);
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    m_musicLibrary.addColumn(MusicLibrary::Title);
    m_musicLibrary.addColumn(MusicLibrary::Artist);
    m_musicLibrary.addColumn(MusicLibrary::Album);
    m_musicLibrary.addColumn(MusicLibrary::Year, Qt::AlignLeft, false);
    m_musicLibrary.addColumn(MusicLibrary::Genre);
    m_musicLibrary.addColumn(MusicLibrary::Length, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(&m_musicBar, BorderLayout::South);
    setLayout(layout);
}

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
