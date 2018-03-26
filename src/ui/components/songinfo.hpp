#ifndef SONGINFO_HPP
#define SONGINFO_HPP

#include <QChar>
#include <QEvent>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QWidget>

#include "src/core/audio.hpp"

class SongInfo : public QWidget
{
public:
    SongInfo(Audio *audio);
    ~SongInfo();

    void init(QList<qint32> stretches);
    void showTrack();
    void showTitle();
    void showArtist();
    void showAlbum();
    void showYear();
    void showGenre();
    void showLength();

private:
    void createLabel(const QString &string, Qt::Alignment align = Qt::AlignLeft);

    QList<QLabel *> m_labels;
    Audio *pm_audio;
};

#endif // SONGINFO_HPP
