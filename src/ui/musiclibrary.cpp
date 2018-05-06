#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param library: library
 * :param parent: parent, default nullptr
 */
MusicLibrary::MusicLibrary(Library *library, QWidget *parent) :
    QListWidget(parent)
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
    setFrameStyle(QFrame::NoFrame);
    setStyleSheet(Utils::read(CSS_MUSICLIBRARY));
    setUniformItemSizes(true);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    Audios audios = pm_library->audios();
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
