#include "librarywidget.hpp"

#include <QHeaderView>

#include "config.hpp"
#include "constants.hpp"
#include "fileutil.hpp"

LibraryWidget::LibraryWidget(QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
    , m_columns()
{
    setup();
}

LibraryWidget::~LibraryWidget()
{

}

void LibraryWidget::setAudios(Audios *audios)
{
    m_audios = audios;

    connect(audios, &Audios::inserted, this, &LibraryWidget::onAudioInserted);
    connect(audios, &Audios::updated, this, &LibraryWidget::onAudiosUpdated);
    connect(audios, &Audios::removed, this, &LibraryWidget::onAudiosRemoved);
}

void LibraryWidget::removeAudios()
{
    if (m_audios)
        disconnect(m_audios, &Audios::inserted, this, &LibraryWidget::onAudioInserted);

    m_audios = nullptr;
}

void LibraryWidget::addColumn(AudioInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void LibraryWidget::onAudiosUpdated(int index)
{
    removeRow(index);
    insert(m_audios->at(index), index);
}

void LibraryWidget::onAudioInserted(int index)
{
    insert(m_audios->at(index), index);
}

void LibraryWidget::onAudiosRemoved(int index)
{
    removeRow(index);
}

void LibraryWidget::insert(Audio *audio, int row)
{
    setUpdatesEnabled(false);

    insertRow(row);
    for (int i = 0; i < m_columns.size(); ++i)
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
    verticalHeader()->setDefaultSectionSize(cfgLibrary.itemHeight());

    setupCss();
}

void LibraryWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfgLibrary.cellPadding()))
        .replace("scrollbar-width", QString::number(cfgLibrary.scrollBarWidth()))
    );
}

QString LibraryWidget::audioText(Audio *audio, int column) const
{
    switch(m_columns[column].info)
    {
        case AudioInfo::Title:
            return audio->title();
        case AudioInfo::Artist:
            return audio->artist();
        case AudioInfo::Album:
            return audio->album();
        case AudioInfo::Track:
            return audio->track() == 0 ? QString() : QString::number(audio->track());
        case AudioInfo::Year:
            return audio->year() == 0 ? QString() : QString::number(audio->year());
        case AudioInfo::Genre:
            return audio->genre();
        case AudioInfo::Duration:
            return audio->duration().toString();
    }
    return QString();
}
