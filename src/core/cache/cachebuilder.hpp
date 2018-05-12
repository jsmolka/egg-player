#ifndef CACHEBUILDER_HPP
#define CACHEBUILDER_HPP

#include <QApplication>
#include <QThread>

#include "audios.hpp"
#include "cache.hpp"

class CacheBuilder : public QThread
{
    Q_OBJECT

public:
    CacheBuilder(QObject *parent = nullptr);
    CacheBuilder(const Audios &audios, QObject *parent = nullptr);
    ~CacheBuilder();

public slots:
    void abort();

protected:
    void run() override;

private:
    Audios m_audios;
    bool m_abort;
};

#endif // CACHEBUILDER_HPP
