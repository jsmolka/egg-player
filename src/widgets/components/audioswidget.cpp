#include "audioswidget.hpp"

#include <QHeaderView>

#include "config.hpp"
#include "constants.hpp"
#include "fileutil.hpp"

AudiosWidget::AudiosWidget(QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
{
    setup();
}

void AudiosWidget::setAudios(Audios *audios)
{
    if (m_audios)
    {
        disconnect(audios, &Audios::inserted, this, &AudiosWidget::onAudioInserted);
        disconnect(audios, &Audios::updated, this, &AudiosWidget::onAudiosUpdated);
        disconnect(audios, &Audios::removed, this, &AudiosWidget::onAudiosRemoved);
    }

    m_audios = audios;

    connect(audios, &Audios::inserted, this, &AudiosWidget::onAudioInserted);
    connect(audios, &Audios::updated, this, &AudiosWidget::onAudiosUpdated);
    connect(audios, &Audios::removed, this, &AudiosWidget::onAudiosRemoved);
}

void AudiosWidget::addColumn(AudioInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void AudiosWidget::onAudiosUpdated(int index)
{
    removeRow(index);
    insert(m_audios->at(index), index);
}

void AudiosWidget::onAudioInserted(int index)
{
    insert(m_audios->at(index), index);
}

void AudiosWidget::onAudiosRemoved(int index)
{
    removeRow(index);
}

void AudiosWidget::insert(Audio *audio, int row)
{
    insertRow(row);
    for (int index = 0; index < m_columns.size(); ++index)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, index));
        item->setTextAlignment(m_columns[index].alignment);
        setItem(row, index, item);
    }
}

void AudiosWidget::setup()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfgLibrary.itemHeight());

    setupCss();
}

void AudiosWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfgLibrary.cellPadding()))
        .replace("scrollbar-width", QString::number(cfgLibrary.scrollBarWidth()))
    );
}

QString AudiosWidget::audioText(Audio *audio, int column) const
{
    switch(m_columns[column].info)
    {
    case AudioInfo::Title:
        return audio->tag().title();
    case AudioInfo::Artist:
        return audio->tag().artist();
    case AudioInfo::Album:
        return audio->tag().album();
    case AudioInfo::Track:
        return audio->tag().track() == 0
            ? QString()
            : QString::number(audio->tag().track());
    case AudioInfo::Year:
        return audio->tag().year() == 0
            ? QString()
            : QString::number(audio->tag().year());
    case AudioInfo::Genre:
        return audio->tag().genre();
    case AudioInfo::Duration:
        return audio->duration().toString();
    }
    return QString();
}
