#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
MusicLibrary::MusicLibrary(QWidget *parent) :
    QListWidget(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setStyleSheet(Utils::read(CSS_MUSICLIBRARY));
    setUniformItemSizes(true);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

/*
 * Destructor.
 */
MusicLibrary::~MusicLibrary()
{

}

/*
 * Loads a library.
 *
 * :param library: library
 */
void MusicLibrary::loadLibrary(Library *library)
{
    clear();

    Audios audios = library->audios();
    for (int i = 0; i < audios.size(); i++)
    {
        SongInfo *info = new SongInfo(audios[i], this);
        info->showTitle();
        info->showArtist();
        info->showAlbum();
        info->showYear();
        info->showGenre();
        info->showLength(Qt::AlignRight);
        info->init({10, 10, 10, 1, 10, 1});
        info->setProperty("even", i % 2 == 0);

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(0, Config::Library::itemHeight()));
        addItem(item);
        setItemWidget(item, info);
    }
}
