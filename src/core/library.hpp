#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <algorithm>

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "cachebuilder.hpp"
#include "audioloader.hpp"

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    ~Library();

    Audios audios() const;
    QStringList paths() const;

    void load(const QStringList &paths);

public slots:
    void insert(Audio *audio);

signals:
    void loaded();
    void AudioInserted(Audio *, int);

private slots:
    void onAudioLoaderFinished();

private:
    Audios m_audios;
    QStringList m_paths;
    CacheBuilder *pm_cacheBuilder;
    AudioLoader *pm_audioLoader;
};

#endif // LIBRARY_HPP
