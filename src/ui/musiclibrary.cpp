#include "musiclibrary.hpp"

MusicLibrary::MusicLibrary(Library *library, QWidget *parent) : QListWidget(parent)
{
    pm_library = library;

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    verticalScrollBar()->setStyleSheet(CSS_SCROLLBAR);
    setFrameStyle(QFrame::NoFrame);

    setupUi();
}

MusicLibrary::~MusicLibrary()
{

}

void MusicLibrary::setupUi()
{
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
        info->setStyleSheet(CSS_SONGINFO);

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(0, 50));
        addItem(item);
        setItemWidget(item, info);
    }
}
