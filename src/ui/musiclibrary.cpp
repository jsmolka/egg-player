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
 * Shows column.
 *
 * :param info: info
 * :param horizontal: horizontal, default left
 * :param expand: expand
 */
void MusicLibrary::showColumn(SongInfo info, Qt::Alignment horizontal, bool expand)
{
    Qt::Alignment alignment = Qt::AlignVCenter | horizontal;
    m_columns << ColumnInfo(info, alignment, expand);
    setColumnCount(m_columns.size());
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
    setUpdatesEnabled(false);

    if (row == -1)
        row = rowCount();
    insertRow(row);

    for (int i = 0; i < m_columns.size(); i++)
    {
        QString text;
        switch(m_columns[i].info)
        {
            case Title:
                text = audio->title();
                break;
            case Artist:
                text = audio->artist();
                break;
            case Album:
                text = audio->album();
                break;
            case Track:
                text = audio->track() == 0 ? QString() : QString::number(audio->track());
                break;
            case Year:
                text = audio->year() == 0 ? QString() : QString::number(audio->year());
                break;
            case Genre:
                text = audio->genre();
                break;
            case Length:
                text = Utils::timeString(audio->length());
                break;
        }

        QTableWidgetItem *item = new QTableWidgetItem(text);
        item->setTextAlignment(m_columns[i].alignment);
        setItem(row, i, item);

        if (!m_columns[i].expand)
            horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    setUpdatesEnabled(true);
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
                "cell-padding",
                QString::number(Config::Library::cellPadding()))
            .replace(
                "scrollbar-width",
                QString::number(Config::Library::scrollBarWidth()));
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
    setStyle(new ClickableStyle(style()));
    setStyleSheet(loadStyleSheet());
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setWordWrap(false);

    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalScrollBar()->hide();
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(Config::Library::itemHeight());
}
