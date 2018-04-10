#include "songinfo.hpp"

SongInfo::SongInfo(Audio *audio, QWidget *parent) : QWidget(parent)
{
    pm_audio = audio;
}

SongInfo::~SongInfo()
{

}

void SongInfo::init(const QList<int> &stretches)
{
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    for (int i = 0; i < m_labels.size(); i++)
    {
        layout->addWidget(m_labels.at(i), 0, i);
        layout->setColumnStretch(i, stretches.at(i));
    }
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
    QString minutes = QString::number(pm_audio->minutes());
    QString length = QString("%1:%2").arg(minutes, seconds);

    createLabel(length, Qt::AlignRight);
}

void SongInfo::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void SongInfo::createLabel(const QString &string, Qt::Alignment align)
{
    QLabel *label = new QLabel(string, this);
    label->setAlignment(align | Qt::AlignVCenter);
    label->setAttribute(Qt::WA_TranslucentBackground);
    m_labels << label;
}
