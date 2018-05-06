#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QObject>
#include <QStringList>

#include "audio.hpp"
#include "audios.hpp"
#include "cache.hpp"
#include "logger.hpp"
#include "utils.hpp"

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    ~Library();

    Audios audios() const;
    bool isEmpty() const;

    void sortByTitle();

    void load(const QStringList &paths);
    void load(const QString &path);

    Audios search(const QString &string, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
    Audio * audioAt(int index);

signals:
    void loaded();

private:
    void loadFromPath(const QString &path);

    Audios m_audios;
};

#endif // LIBRARY_HPP
