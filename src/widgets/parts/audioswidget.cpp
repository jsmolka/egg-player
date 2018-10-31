#include "audioswidget.hpp"

#include <QHeaderView>

#include "core/globals.hpp"

AudiosWidget::AudiosWidget(QWidget *parent)
    : AudiosWidget(nullptr, parent)
{

}

AudiosWidget::AudiosWidget(Audios *audios, QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
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
    m_audios = audios;

    if (!audios)
        return;

    connect(audios, &Audios::inserted, this, &AudiosWidget::onAudiosInserted);
    connect(audios, &Audios::removed, this, &AudiosWidget::onAudiosRemoved);
    connect(audios, &Audios::updated, this, &AudiosWidget::onAudiosUpdated);

    for (int row = 0; row < audios->size(); ++row)
        insert(row, audios->at(row));
}

Audios *AudiosWidget::audios() const
{
    return m_audios;
}

void AudiosWidget::addColumn(AudioInfo info, Qt::Alignment align, SizePolicy policy)
{
    Column column;
    column.info = info;
    column.align = align | Qt::AlignVCenter;
    m_columns << column;

    setColumnCount(m_columns.size());

    if (policy == SizePolicy::Shrink)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void AudiosWidget::onAudiosInserted(int row)
{
    insert(row, m_audios->at(row));
}

void AudiosWidget::onAudiosRemoved(int row)
{
    removeRow(row);
}

void AudiosWidget::onAudiosUpdated(int row)
{
    Audio *audio = m_audios->at(row);

    for (int col = 0; col < m_columns.size(); ++col)
    {
        const Column column = m_columns.at(col);

        QTableWidgetItem *item = takeItem(row, col);
        item->setText(audioInfo(audio, column.info));
        setItem(row, col, item);
    }
}

void AudiosWidget::setup()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfg_library.itemHeight());

    setupCss();
}

void AudiosWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfg_library.cellPadding()))
        .replace("scrollbar-width", QString::number(cfg_library.scrollBarWidth()))
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

void AudiosWidget::insert(int row, Audio *audio)
{
    insertRow(row);

    for (int col = 0; col < m_columns.size(); ++col)
    {
        const Column column = m_columns.at(col);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(audioInfo(audio, column.info));
        item->setTextAlignment(column.align);
        setItem(row, col, item);
    }
}
