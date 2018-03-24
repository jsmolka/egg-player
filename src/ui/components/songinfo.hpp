#ifndef SONGINFO_HPP
#define SONGINFO_HPP

#include <QChar>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QString>
#include <QWidget>

#include "src/core/audio.hpp"

class SongInfo : public QWidget
{
public:
    SongInfo(Audio *audio);
    ~SongInfo();

    void init();
    void showTrack();
    void showTitle();
    void showArtist();
    void showAlbum();
    void showYear();
    void showGenre();
    void showLength();

private:
    void createLabel(const QString &string);

    QList<QLabel *> m_labels;
    Audio *pm_audio;
};

#endif // SONGINFO_HPP
