#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
MusicLibrary::MusicLibrary(QWidget *parent) :
    QListWidget(parent)
{
    setAlternatingRowColors(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setSelectionMode(QListWidget::NoSelection);
    setStyleSheet(loadStyleSheet());
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

    for (Audio *audio : library->audios())
    {
        SongInfo *info = new SongInfo(audio, this);
        info->showTitle();
        info->showArtist();
        info->showAlbum();
        info->showYear();
        info->showGenre();
        info->showLength(Qt::AlignRight);
        info->init({10, 10, 10, 1, 10, 1});

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(0, Config::Library::itemHeight()));
        addItem(item);
        setItemWidget(item, info);
    }
}

/*
 * Loads style sheet and replaces placeholders.
 *
 * :return: style sheet
 */
QString MusicLibrary::loadStyleSheet()
{
    return Utils::read(CSS_MUSICLIBRARY)
            .replace(
                "scrollbar-width",
                QString::number(Config::Library::scrollBarWidth()));

}
