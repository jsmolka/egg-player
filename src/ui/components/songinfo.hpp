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
    SongInfo(QWidget *parent = nullptr);
    SongInfo(Audio *audio, QWidget *parent = nullptr);
    ~SongInfo();

    void init(const QVector<int> &stretches);
    void showTrack(Qt::Alignment horizontal = Qt::AlignLeft);
    void showTitle(Qt::Alignment horizontal = Qt::AlignLeft);
    void showArtist(Qt::Alignment horizontal = Qt::AlignLeft);
    void showAlbum(Qt::Alignment horizontal = Qt::AlignLeft);
    void showYear(Qt::Alignment horizontal = Qt::AlignLeft);
    void showGenre(Qt::Alignment horizontal = Qt::AlignLeft);
    void showLength(Qt::Alignment horizontal = Qt::AlignLeft);

protected:
    void paintEvent(QPaintEvent *);

private:
    void createLabel(const QString &text = QString(), Qt::Alignment horizontal = Qt::AlignLeft);

    QVector<QLabel *> m_labels;
    Audio *pm_audio;
};

#endif // SONGINFO_HPP
