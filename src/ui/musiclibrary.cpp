#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
MusicLibrary::MusicLibrary(QWidget *parent) :
    QTableWidget(parent)
{
    setAlternatingRowColors(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    //setSelectionMode(QListWidget::NoSelection);
    setStyleSheet(loadStyleSheet());
    //setUniformItemSizes(true);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setWordWrap(false);

    verticalHeader()->hide();
    horizontalHeader()->hide();
    horizontalScrollBar()->hide();
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
    setRowCount(library->audios().size());
    setColumnCount(6);
    int i = 0;
    for (Audio *audio : library->audios())
    {
        /*SongInfo *info = new SongInfo(audio, this);
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
        setItemWidget(item, info);*/
        setRowHeight(i, Config::Library::itemHeight());

        QTableWidgetItem *item = new QTableWidgetItem(audio->title());
        setItem(i, 0, item);
        item = new QTableWidgetItem(audio->artist());
        setItem(i, 1, item);
        item = new QTableWidgetItem(audio->album());
        setItem(i, 2, item);
        item = new QTableWidgetItem(QString::number(audio->year()));
        setItem(i, 3, item);
        item = new QTableWidgetItem(audio->genre());
        setItem(i, 4, item);
        item = new QTableWidgetItem(Utils::timeString(audio->length()));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        setItem(i, 5, item);
        i++;
    }
    resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
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
