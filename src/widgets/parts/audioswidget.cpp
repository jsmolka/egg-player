#include "audioswidget.hpp"

#include <QHeaderView>

AudiosWidget::AudiosWidget(QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
{
    setup();
}

void AudiosWidget::setAudios(Audios *audios)
{
    if (m_audios)
        disconnect(audios, nullptr, this, nullptr);

    m_audios = audios;

    connect(m_audios, &Audios::inserted, this, &AudiosWidget::onAudiosInserted);
    connect(m_audios, &Audios::updated, this, &AudiosWidget::onAudiosUpdated);
    connect(m_audios, &Audios::removed, this, &AudiosWidget::onAudiosRemoved);
    connect(m_audios, &Audios::moved, this, &AudiosWidget::onAudiosMoved);
}

Audios *AudiosWidget::audios() const
{
    return m_audios;
}

void AudiosWidget::addColumn(AudioInfo::Info info, Qt::Alignment horizontal, bool expand)
{
    Column column;
    column.info = info;
    column.alignment = Qt::AlignVCenter | horizontal;
    m_columns << column;

    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void AudiosWidget::onAudiosUpdated(int row)
{
    Audio *audio = m_audios->at(row);
    for (int column = 0; column < m_columns.size(); ++column)
    {
        QTableWidgetItem *item = takeItem(row, column);
        item->setText(audioText(audio, column));
        setItem(row, column, item);
    }
}

void AudiosWidget::onAudiosInserted(int row)
{
    insert(m_audios->at(row), row);
}

void AudiosWidget::onAudiosRemoved(int row)
{
    removeRow(row);
}

void AudiosWidget::onAudiosMoved(int from, int to)
{
    onAudiosRemoved(from);
    onAudiosInserted(to);
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

void AudiosWidget::insert(Audio *audio, int row)
{
    insertRow(row);
    for (int column = 0; column < m_columns.size(); ++column)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, column));
        item->setTextAlignment(m_columns[column].alignment);
        setItem(row, column, item);
    }
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
        return audio->tag().track() != 0
            ? QString::number(audio->tag().track())
            : QString();
    case AudioInfo::Year:
        return audio->tag().year() != 0
            ? QString::number(audio->tag().year())
            : QString();
    case AudioInfo::Genre:
        return audio->tag().genre();
    case AudioInfo::Duration:
        return audio->duration().toString();
    }
    return QString();
}
