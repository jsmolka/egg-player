#ifndef CACHEBUILDER_HPP
#define CACHEBUILDER_HPP

#include <QApplication>
#include <QThread>

#include "audiolist.hpp"
#include "cache.hpp"

/*
 * The CacheBuilder class is a thread which gets
 * started after loading the library. It caches
 * all audio covers in the background for later use.
 */
class CacheBuilder : public QThread
{
    Q_OBJECT

public:
    CacheBuilder(const AudioList &audioList);
    ~CacheBuilder();

public slots:
    void abort();

protected:
    void run() override;

private:
    AudioList m_audioList;
    bool m_abort;
};

#endif // CACHEBUILDER_HPP
