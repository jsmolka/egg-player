#include "songlist.hpp"

SongList::SongList(Library *library) : QListWidget()
{
    pm_library = library;

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setupUi();
}

void SongList::setupUi()
{
    int idx = 0;
    for (Audio audio : pm_library->audioList())
    {
        QLabel *label = new QLabel(audio.title());
        if (idx % 2 == 0)
            label->setStyleSheet("QLabel {color: white; background-color: #4d4d4d;}");
        else
            label->setStyleSheet("QLabel {color: white; background-color: #333333;}");
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 55));
        addItem(item);
        setItemWidget(item, label);
        idx++;
    }
}
