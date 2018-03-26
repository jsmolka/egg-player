#include "musiclibrary.hpp"

MusicLibrary::MusicLibrary(Library *library) : QListWidget()
{
    pm_library = library;

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    verticalScrollBar()->setStyleSheet(CSS_SCROLLBAR);
    setFrameStyle(QFrame::NoFrame);

    setupUi();
}

void MusicLibrary::setupUi()
{
    AudioList audioList = pm_library->audioList();
    for (int i = 0; i < audioList.size(); i++)
    {
        SongInfo *info = new SongInfo(&audioList[i]);
        info->showTitle();
        info->showArtist();
        info->showAlbum();
        info->showYear();
        info->showGenre();
        info->showLength();
        info->init({10, 10, 10, 1, 10, 1});
        info->setStyleSheet(i % 2 == 0 ? CSS_SONGINFO_EVEN : CSS_SONGINFO_ODD);

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 50));
        addItem(item);
        setItemWidget(item, info);
    }
}
