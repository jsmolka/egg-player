#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QPixmap>

#include "audio.hpp"
#include "database.hpp"

class Cache : private Database
{
public:
    void initialize();

    Audio *loadAudio(const File &file);
    void insertAudio(Audio *audio);
    void updateAudio(Audio *audio, const File &newFile = File());

    int insertCover(const QPixmap &cover);
    void updateCover(const QPixmap &cover);
    void setAudioCoverId(Audio *audio, int id);
    void updateAudioCover(Audio *audio, const QPixmap &cover);

    QPixmap coverById(int id);

private:
    static QByteArray coverToBytes(const QPixmap &cover);

    void createCovers();
    void createAudios();
    bool defaultCoverExists();
    void insertDefaultCover();

    int insertByteCover(const QByteArray &bytes);
    void updateByteCover(int id, const QByteArray &bytes);

    int coverId(const QByteArray &bytes);
    int lastCoverId();
    int coverIdBySize(int size);
    int coverIdByBlob(const QByteArray &bytes);
};

#endif // CACHE_HPP
