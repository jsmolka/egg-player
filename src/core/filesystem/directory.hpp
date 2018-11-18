#ifndef DIRECTORY2_HPP
#define DIRECTORY2_HPP

#include <QHash>
#include <QObject>
#include <QSet>

#include "core/macros.hpp"
#include "core/types.hpp"

namespace fs
{

class Directory : public QObject
{
    Q_OBJECT

public:
    enum AddPolicy {Process, Ignore};

    explicit Directory(const QString &path, QObject *parent = nullptr);

    EGG_PPROP(AddPolicy, addPolicy, setAddPolicy, addPolicy)

    QString path() const;
    QSet<QString> files() const;
    QHash<QString, Directory *> subdirs() const;

    bool exists() const;

    void init();

    QStrings update();

signals:
    void added(Directory *dir);
    void removed(Directory *dir);

private:
    QStrings deleteRecursive(Directory *dir);

    void processRemovedDirChanges(QStrings &changes);
    void processExistingDirChanges(QStrings &changes);
    void processFileChanges(QStrings &changes);

    QString m_path;
    QSet<QString> m_files;
    QHash<QString, Directory *> m_subdirs;
};

}

#endif // DIRECTORY2_HPP
