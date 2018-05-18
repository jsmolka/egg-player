#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "audioloader.hpp"
#include "cachebuilder.hpp"
#include "threadpool.hpp"

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    Library(bool sorted, QObject *parent = nullptr);
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
    void onPoolFinished();

private:
    int lowerBound(Audio *audio);
    void insertBinary(Audio *audio);
    void append(Audio *audio);

    bool m_sorted;
    Audios m_audios;
    ThreadPool *pm_pool;
};

#endif // LIBRARY_HPP
