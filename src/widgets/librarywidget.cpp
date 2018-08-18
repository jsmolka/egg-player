#include "librarywidget.hpp"

LibraryWidget::LibraryWidget(QWidget *parent)
    : TableWidget(parent)
{
    setup();
}

LibraryWidget::~LibraryWidget()
{

}

void LibraryWidget::setLibrary(Library *library)
{
    m_library = library;

    connect(library->audios(), &Audios::inserted, this, &LibraryWidget::onAudioInserted);
    connect(library->audios(), &Audios::updated, this, &LibraryWidget::onAudiosUpdated);
    connect(library->audios(), &Audios::removed, this, &LibraryWidget::onAudiosRemoved);
}

void LibraryWidget::removeLibrary()
{
    disconnect(m_library, &Library::inserted, this, &LibraryWidget::insert);

    m_library = nullptr;
}

void LibraryWidget::addColumn(SongInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void LibraryWidget::onAudiosUpdated(Audio *audio)
{
    int row = m_library->audios()->indexOf(audio);
    removeRow(row);
    insert(audio, row);
}

void LibraryWidget::onAudioInserted(int index)
{
    insert(m_library->audios()->at(index), index);
}

void LibraryWidget::onAudiosRemoved(int index)
{
    removeRow(index);
}

void LibraryWidget::insert(Audio *audio, int row)
{
    setUpdatesEnabled(false);

    insertRow(row);
    for (int i = 0; i < m_columns.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, i));
        item->setTextAlignment(m_columns[i].alignment);
        setItem(row, i, item);
    }

    setUpdatesEnabled(true);
}

void LibraryWidget::setup()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfgLibrary->itemHeight());

    setupCss();
}

void LibraryWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfgLibrary->cellPadding()))
        .replace("scrollbar-width", QString::number(cfgLibrary->scrollBarWidth()))
    );
}

QString LibraryWidget::audioText(Audio *audio, int column)
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
        case SongInfo::Duration:
            return audio->duration()->toString();
    }
    return QString();
}
