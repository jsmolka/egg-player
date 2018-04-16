#ifndef SONGINFO_HPP
#define SONGINFO_HPP

#include <QGridLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QWidget>

#include "audio.hpp"

class SongInfo : public QWidget
{
    Q_OBJECT

public:
    SongInfo(Audio *audio, QWidget *parent = nullptr);
    ~SongInfo();

    void init(const QList<int> &stretches);
    void showTrack();
    void showTitle();
    void showArtist();
    void showAlbum();
    void showYear();
    void showGenre();
    void showLength();

protected:
    void paintEvent(QPaintEvent *);

private:
    void createLabel(const QString &string, Qt::Alignment align = Qt::AlignLeft);

    QList<QLabel *> m_labels;
    Audio *pm_audio;
};

#endif // SONGINFO_HPP
