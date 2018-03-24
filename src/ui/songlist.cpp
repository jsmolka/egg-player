#include "songlist.hpp"

SongList::SongList(Library *library) : QListWidget()
{
    pm_library = library;

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);

    setupUi();
}

void SongList::setupUi()
{
    QString cssEven = FileUtil::read(CSS_SONGINFO_EVEN);
    QString cssOdd = FileUtil::read(CSS_SONGINFO_ODD);

    int i = 0;
    for (Audio audio : pm_library->audioList())
    {
        SongInfo *info = new SongInfo(&audio);
        info->showTitle();
        info->showArtist();
        info->showAlbum();
        info->showYear();
        info->showGenre();
        info->showLength();
        info->init({10, 10, 10, 1, 10, 1});
        info->setStyleSheet(i % 2 == 0 ? cssEven : cssOdd);

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 50));
        addItem(item);
        setItemWidget(item, info);

        i++;
    }
}
