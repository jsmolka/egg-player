#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QObject>
#include <QStringList>
#include <QThread>

#include "audio.hpp"
#include "audiolist.hpp"
#include "cache.hpp"
#include "fileutil.hpp"
#include "logger.hpp"

class CacheBuilder : public QThread
{
    Q_OBJECT

public:
    CacheBuilder(const AudioList &audioList, QObject *parent = nullptr);

protected:
    void run() override;

private:
    AudioList m_audioList;
};

class Library : public QObject
{
    Q_OBJECT

public:
    Library(const QString &path, QObject *parent = nullptr);
    ~Library();

    AudioList audioList() const;
    bool isEmpty() const;

    void sortByTitle();

    AudioList search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    Audio * audioAt(int index);

private:
    void loadFiles(const QString &path);

    AudioList m_audioList;
};

#endif // LIBRARY_HPP
