#include "audioswidget.hpp"

#include <QHeaderView>
#include <QKeyEvent>

#include "core/config.hpp"
#include "core/constants.hpp"
#include "core/utils.hpp"

AudiosWidget::AudiosWidget(QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
    , m_finder(this)
{
    init();
}

AudiosWidget::AudiosWidget(Audios *audios, QWidget *parent)
    : AudiosWidget(parent)
{
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
    m_finder.setAudios(audios);

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

void AudiosWidget::addColumn(AudioInfo info, Qt::Alignment align, ColumnSizePolicy policy)
{
    Column column;
    column.info = info;
    column.align = align | Qt::AlignVCenter;
    m_columns << column;

    setColumnCount(m_columns.size());

    if (policy == ColumnSizePolicy::Shrink)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void AudiosWidget::keyboardSearch(const QString &search)
{
    Q_UNUSED(search)
}

void AudiosWidget::keyPressEvent(QKeyEvent *event)
{
    m_finder.addKey(event->text());
    const int row = m_finder.search();
    if (row != -1)
    {
        scrollTo(model()->index(row, 0));
        setHoverRow(row);
    }
    TableWidget::keyPressEvent(event);
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
    const Audio &audio = m_audios->at(row);

    int col = 0;
    for (const Column &column : m_columns)
    {
        QTableWidgetItem *item = takeItem(row, col);
        item->setText(audioInfo(audio, column.info));
        setItem(row, col, item);
        col++;
    }
}

QString AudiosWidget::audioInfo(const Audio &audio, AudioInfo info)
{
    switch(info)
    {
    case AudioInfo::Title:
        return audio.tag().title();

    case AudioInfo::Artist:
        return audio.tag().artist();

    case AudioInfo::Album:
        return audio.tag().album();

    case AudioInfo::Track:
        return audio.tag().track() != 0
            ? QString::number(audio.tag().track())
            : QString();

    case AudioInfo::Year:
        return audio.tag().year() != 0
            ? QString::number(audio.tag().year())
            : QString();

    case AudioInfo::Genre:
        return audio.tag().genre();

    case AudioInfo::Duration:
        return audio.duration().toString();
    }
    return QString();
}

void AudiosWidget::insert(int row, const Audio &audio)
{
    insertRow(row);

    int col = 0;
    for (const Column &column : m_columns)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(audioInfo(audio, column.info));
        item->setTextAlignment(column.align);
        setItem(row, col, item);
        col++;
    }
}

void AudiosWidget::init()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfg_library.itemHeight());

    initStyle();
}

void AudiosWidget::initStyle()
{
    setStyleSheet(FileUtil::read(constants::css::Library)
        .replace("cell-padding", QString::number(cfg_library.cellPadding()))
        .replace("scrollbar-width", QString::number(cfg_library.scrollBarWidth()))
    );
}
