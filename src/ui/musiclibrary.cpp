#include "musiclibrary.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
MusicLibrary::MusicLibrary(QWidget *parent) :
    QTableWidget(parent)
{
    setup();
}

/*
 * Destructor.
 */
MusicLibrary::~MusicLibrary()
{

}

/*
 * Loads audios.
 *
 * :param audios: audios
 */
void MusicLibrary::loadAudios(Audios audios)
{
    clear();

    setRowCount(audios.size());
    setColumnCount(6);

    setUpdatesEnabled(false);
    int i = 0;
    for (Audio *audio : audios)
    {
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
    setUpdatesEnabled(true);

    resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
}

/*
 * Loads a library.
 *
 * :param library: library
 */
void MusicLibrary::loadLibrary(Library *library)
{
    loadAudios(library->audios());
}

/*
 * Sets up widget.
 */
void MusicLibrary::setup()
{
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setItemDelegate(new RowHoverDelegate(this, this));
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setStyleSheet(loadStyleSheet());
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setWordWrap(false);

    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalScrollBar()->hide();
    verticalHeader()->hide();
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
