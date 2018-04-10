#include "musiclibrary.hpp"

MusicLibrary::MusicLibrary(Library *library, QWidget *parent) : QListWidget(parent)
{
    pm_library = library;

    setupUi();
}

MusicLibrary::~MusicLibrary()
{

}

void MusicLibrary::setupUi()
{
    setStyleSheet(CSS_MUSICLIBRARY);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setFrameStyle(QFrame::NoFrame);

    AudioList audioList = pm_library->audioList();

    for (int i = 0; i < audioList.size(); i++)
    {
        SongInfo *info = new SongInfo(audioList[i], this);
        info->showTitle();
        info->showArtist();
        info->showAlbum();
        info->showYear();
        info->showGenre();
        info->showLength();
        info->init({10, 10, 10, 1, 10, 1});

        info->setProperty("even", i % 2 == 0);

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(0, Config::mlSongInfoHeight()));
        addItem(item);
        setItemWidget(item, info);
    }
}
