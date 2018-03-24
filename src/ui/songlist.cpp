#include "songlist.hpp"

SongList::SongList(Library *library) : QListWidget()
{
    pm_library = library;

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setupUi();
}

void SongList::setupUi()
{
    QString cssEven = FileUtil::read(CSS_SONGINFO_EVEN);
    QString cssOdd = FileUtil::read(CSS_SONGINFO_ODD);

    int index = 0;
    for (Audio audio : pm_library->audioList())
    {
        SongInfo *info = new SongInfo(&audio);
        info->showTrack();
        info->showTitle();
        info->showAlbum();
        info->showArtist();
        info->showYear();
        info->showGenre();
        info->showLength();
        info->init();
        info->setStyleSheet(index % 2 == 0 ? cssEven : cssOdd);

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 55));
        addItem(item);
        setItemWidget(item, info);
        index++;
    }
}
