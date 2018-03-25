#include "musicwindow.hpp"

MusicWindow::MusicWindow(Library *library) : QListWidget()
{
    pm_library = library;

    setupUi();
}

void MusicWindow::setupUi()
{
    QString cssEven = FileUtil::read(CSS_SONGINFO_EVEN);
    QString cssOdd = FileUtil::read(CSS_SONGINFO_ODD);

    AudioList audios = pm_library->audioList();
    for (int i = 0; i < audios.size(); i++)
    {
        SongInfo *info = new SongInfo(&audios[i]);
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
    }
}
