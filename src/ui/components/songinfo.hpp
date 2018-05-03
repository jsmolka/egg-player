#ifndef SONGINFO_HPP
#define SONGINFO_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVector>
#include <QWidget>

#include "audio.hpp"
#include "utils.hpp"

class SongInfo : public QWidget
{
    Q_OBJECT

public:
    SongInfo(Audio *audio, QWidget *parent = nullptr);
    ~SongInfo();

    void init(const QVector<int> &stretches);
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
    void createLabel(const QString &text = QString(), Qt::Alignment align = Qt::AlignLeft);

    QVector<QLabel *> m_labels;
    Audio *pm_audio;
};

#endif // SONGINFO_HPP
