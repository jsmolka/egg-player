#ifndef LIBRARY_HPP
#define LIBRARY_HPP

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

    void setSorted(bool sorted);
    bool isSorted() const;
    Audios audios() const;

    void load(const QStringList &paths);

public slots:
    void insert(Audio *audio);

signals:
    void loaded();
    void inserted(Audio *, int);

private slots:
    void onAudioLoaderFinished();

private:
    int lowerBound(Audio *audio);
    void insertBinary(Audio *audio);
    void append(Audio *audio);

    bool m_sorted;
    Audios m_audios;
    CacheBuilder *pm_cacheBuilder;
    AudioLoader *pm_audioLoader;
};

#endif // LIBRARY_HPP
