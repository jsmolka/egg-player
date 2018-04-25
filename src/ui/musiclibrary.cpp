#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param library: library pointer
 * :param parent: parent pointer
 */
MusicLibrary::MusicLibrary(Library *library, QWidget *parent) : QListWidget(parent)
{
    pm_library = library;

    setupUi();
}

/*
 * Destructor.
 */
MusicLibrary::~MusicLibrary()
{

}

/*
 * Sets up user interface.
 */
void MusicLibrary::setupUi()
{
    setStyleSheet(Utils::read(CSS_MUSICLIBRARY));
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
        item->setSizeHint(QSize(0, Config::LItemHeight()));
        addItem(item);
        setItemWidget(item, info);
    }
}
