#include "songinfo.hpp"

SongInfo::SongInfo(Audio *audio) : QWidget()
{
    pm_audio = audio;
}

SongInfo::~SongInfo()
{
    for (QLabel *label : m_labels)
        delete label;
}

void SongInfo::init(QList<qint32> stretches)
{
    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < m_labels.size(); i++)
    {
        layout->addWidget(m_labels.at(i), 0, i);
        layout->setColumnStretch(i, stretches.at(i));
    }
    setLayout(layout);
}

void SongInfo::showTrack()
{
    createLabel(QString::number(pm_audio->track()));
}

void SongInfo::showTitle()
{
    createLabel(pm_audio->title());
}

void SongInfo::showArtist()
{
    createLabel(pm_audio->artist());
}

void SongInfo::showAlbum()
{
    createLabel(pm_audio->album());
}

void SongInfo::showYear()
{
    createLabel(QString::number(pm_audio->year()));
}

void SongInfo::showGenre()
{
    createLabel(pm_audio->genre());
}

void SongInfo::showLength()
{
    QString seconds = QString("%1").arg(pm_audio->seconds(), 2, 10, QChar('0'));
    createLabel(QString("%1:%2").arg(QString::number(pm_audio->minutes()), seconds), Qt::AlignRight);
}

void SongInfo::createLabel(const QString &string, Qt::Alignment align)
{
    QLabel *label = new QLabel(string, this);
    label->setAlignment(align | Qt::AlignVCenter);
    label->setAttribute(Qt::WA_TranslucentBackground);
    m_labels << label;
}
