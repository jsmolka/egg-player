#ifndef FS_DIRECTORY_HPP
#define FS_DIRECTORY_HPP

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
    enum AddPolicy {Allow, Ignore};

    explicit Directory(const QString &path, QObject *parent = nullptr);

    EGG_P_PROP(AddPolicy, addPolicy, setAddPolicy, addPolicy)

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
    void processRemovedSubdirs(QStrings &changes);
    void processCurrentSubdirs(QStrings &changes);
    void processRemovedFiles(QStrings &changes);
    void processCurrentFiles(QStrings &changes);

    QStrings deleteRecursive(Directory *dir);

    QString m_path;
    QSet<QString> m_files;
    QHash<QString, Directory *> m_subdirs;
};

}

#endif // FS_DIRECTORY_HPP
