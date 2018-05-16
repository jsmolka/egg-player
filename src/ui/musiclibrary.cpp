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
 * Inserts audio into library. If row is
 * -1 it will be appended to the last one.
 *
 * :param audio: audio
 * :param row: row, default -1
 */
void MusicLibrary::insert(Audio *audio, int row)
{
    if (row == -1)
        row = rowCount();

    setColumnCount(6);

    insertRow(row);

    setRowHeight(row, Config::Library::itemHeight());
    QTableWidgetItem *item = new QTableWidgetItem(audio->title());
    setItem(row, 0, item);
    item = new QTableWidgetItem(audio->artist());
    setItem(row, 1, item);
    item = new QTableWidgetItem(audio->album());
    setItem(row, 2, item);
    item = new QTableWidgetItem(QString::number(audio->year()));
    setItem(row, 3, item);
    item = new QTableWidgetItem(audio->genre());
    setItem(row, 4, item);
    item = new QTableWidgetItem(Utils::timeString(audio->length()));
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row, 5, item);

    //resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
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
