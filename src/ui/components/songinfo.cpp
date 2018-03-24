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

void SongInfo::init()
{
    QGridLayout *layout = new QGridLayout;

    int index = 0;
    for (QLabel *label : m_labels)
    {
        layout->addWidget(label, 0, index);
        index++;
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
    createLabel(QString("%1:%2").arg(QString::number(pm_audio->minutes()), seconds));
}

void SongInfo::createLabel(const QString &string)
{
    QLabel *label = new QLabel(string, this);
    label->setMargin(10);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_labels << label;
}
