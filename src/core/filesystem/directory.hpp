#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <QHash>
#include <QObject>
#include <QSet>

#include "core/globals.hpp"

class Directory : public QObject
{
    Q_OBJECT

public:
    enum GlobPolicy {Recursive, Shallow};

    explicit Directory(QObject *parent = nullptr);
    explicit Directory(const QString &path, QObject *parent = nullptr);

    QString path() const;
    QSet<QString> files() const;
    QHash<QString, Directory *> dirs() const;

    bool exists() const;

    void parse();

    QStrings globAudios(GlobPolicy policy = GlobPolicy::Recursive) const;
    QStrings processChanges();

signals:
    void parsed(Directory *dir);
    void created(Directory *dir);
    void removed(Directory *dir);

private:
    void processRemovedDirChanges(QStrings &changes);
    void processExistingDirChanges(QStrings &changes);
    void processFileChanges(QStrings &changes);

    QString m_path;
    QSet<QString> m_files;
    QHash<QString, Directory *> m_dirs;
};

#endif // DIRECTORY_HPP
