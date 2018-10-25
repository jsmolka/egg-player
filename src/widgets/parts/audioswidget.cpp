#include "audioswidget.hpp"

#include <QHeaderView>

AudiosWidget::AudiosWidget(QWidget *parent)
    : AudiosWidget(nullptr, parent)
{

}

AudiosWidget::AudiosWidget(Audios *audios, QWidget *parent)
    : TableWidget(parent)
    , m_audios(audios)
{
    setup();

    setAudios(audios);
}

void AudiosWidget::setAudios(Audios *audios)
{    
    if (m_audios)
    {
        disconnect(m_audios, nullptr, this, nullptr);
        clearContents();
    }

    if (!audios)
        return;

    m_audios = audios;
    connect(audios, &Audios::inserted, this, &AudiosWidget::onAudiosInserted);
    connect(audios, &Audios::updated, this, &AudiosWidget::onAudiosUpdated);
    connect(audios, &Audios::removed, this, &AudiosWidget::onAudiosRemoved);
    connect(audios, &Audios::moved, this, &AudiosWidget::onAudiosMoved);

    for (int row = 0; row < audios->size(); ++row)
        insert(audios->at(row), row);
}

Audios *AudiosWidget::audios() const
{
    return m_audios;
}

void AudiosWidget::addColumn(AudioInfo info, Qt::Alignment align, SizePolicy policy)
{
    m_columns << qMakePair(info, Qt::AlignVCenter | align);
    setColumnCount(m_columns.size());

    if (policy == SizePolicy::Shrink)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void AudiosWidget::onAudiosUpdated(int row)
{
    Audio *audio = m_audios->at(row);

    for (int col = 0; col < m_columns.size(); ++col)
    {
        const Column column = m_columns.at(col);

        QTableWidgetItem *item = takeItem(row, col);
        item->setText(audioInfo(audio, column.first));
        setItem(row, col, item);
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

QString AudiosWidget::audioInfo(Audio *audio, AudioInfo info)
{
    switch(info)
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

void AudiosWidget::insert(Audio *audio, int row)
{
    insertRow(row);

    for (int col = 0; col < m_columns.size(); ++col)
    {
        const Column column = m_columns.at(col);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(audioInfo(audio, column.first));
        item->setTextAlignment(column.second);
        setItem(row, col, item);
    }
}
