#include "songlist.hpp"

SongList::SongList(Library *library) : QListWidget()
{
    pm_library = library;

    setupUi();
}

void SongList::setupUi()
{
    int idx = 0;
    for (Audio audio : pm_library->audioList())
    {
        QLabel *label = new QLabel(audio.title());
        if (idx % 2 == 0)
            label->setStyleSheet("QLabel {background-color: white;}");
        else
            label->setStyleSheet("QLabel {background-color: grey;}");
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 65));
        addItem(item);
        setItemWidget(item, label);
        idx++;
    }
}
