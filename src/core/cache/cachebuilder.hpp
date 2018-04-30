#ifndef CACHEBUILDER_HPP
#define CACHEBUILDER_HPP

#include <QApplication>
#include <QThread>

#include "audiolist.hpp"
#include "cache.hpp"

class CacheBuilder : public QThread
{
    Q_OBJECT

public:
    CacheBuilder(const AudioList &audioList, QObject *parent = nullptr);
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
