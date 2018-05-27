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

    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(onEntered(QModelIndex)));
}

/*
 * Destructor.
 */
MusicLibrary::~MusicLibrary()
{

}

/*
 * Shows a column.
 *
 * :param info: info
 * :param horizontal: horizontal, default left
 * :param expand: expand, default true
 */
void MusicLibrary::addColumn(SongInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

/*
 * Inserts an audio into the library. Append a row if -1.
 *
 * :param audio: audio
 * :param row: row, default -1
 */
void MusicLibrary::insert(Audio *audio, int row)
{
    setUpdatesEnabled(false);

    if (row == -1)
        row = rowCount();
    insertRow(row);

    for (int i = 0; i < m_columns.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, i));
        item->setTextAlignment(m_columns[i].alignment);
        setItem(row, i, item);
    }
    setUpdatesEnabled(true);
}

/*
 * Emits -1 to remove the row hover style.
 *
 * :param event: event
 * :emit hoverRowChanged: row
 */
void MusicLibrary::leaveEvent(QEvent *event)
{
    emit hoverRowChanged(-1);

    QTableWidget::leaveEvent(event);
}

/*
 * Emits the row where the cursor is hovering over. Calls the resize event first
 * to get the cursor position for the resized widget.
 *
 * :param event: event
 * :emit hoverRowChanged: row
 */
void MusicLibrary::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);

    emit hoverRowChanged(indexAt(mapFromGlobal(QCursor::pos())).row());
}

/*
 * Emits the row of the entered item.
 *
 * :param index: index
 * :emit hoverRowChanged: row
 */
void MusicLibrary::onEntered(QModelIndex index)
{
    emit hoverRowChanged(index.row());
}

/*
 * Loads the style sheet and replaces placeholders.
 */
void MusicLibrary::loadCss()
{
    setStyleSheet(
        FileUtil::read(CSS_MUSICLIBRARY)
            .replace("cell-padding", QString::number(Config::Library::cellPadding()))
            .replace("scrollbar-width", QString::number(Config::Library::scrollBarWidth()))
    );
}

/*
 * Sets up widget.
 */
void MusicLibrary::setup()
{
    loadCss();

    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setItemDelegate(new RowHoverDelegate(this, this));
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setWordWrap(false);

    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(Config::Library::itemHeight());

    horizontalScrollBar()->hide();
    verticalScrollBar()->setStyle(new ClickableStyle(style()));
}

/*
 * Gets audio text for a given column.
 *
 * :param audio: audio
 * :param column: column
 * :return: audio text
 */

QString MusicLibrary::audioText(Audio *audio, int column)
{
    switch(m_columns[column].info)
    {
        case SongInfo::Title:
            return audio->title();
        case SongInfo::Artist:
            return audio->artist();
        case SongInfo::Album:
            return audio->album();
        case SongInfo::Track:
            return audio->track() == 0 ? QString() : QString::number(audio->track());
        case SongInfo::Year:
            return audio->year() == 0 ? QString() : QString::number(audio->year());
        case SongInfo::Genre:
            return audio->genre();
        case SongInfo::Length:
            return Util::time(audio->length());
    }
    return QString();
}
