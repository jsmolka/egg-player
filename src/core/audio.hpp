#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QDateTime>
#include <QFileInfo>
#include <QObject>
#include <QVector>

#include "cover.hpp"
#include "tag.hpp"
#include "types.hpp"

class Audio : public QObject
{
    Q_OBJECT

public:
    using vector = QVector<Audio *>;

    explicit Audio(QObject *parent = nullptr);
    explicit Audio(const File &file, QObject *parent = nullptr);

    void setFile(const File &file);
    File file() const;

    void setValid(bool valid);
    bool isValid() const;

    void setCached(bool cached);
    bool isCached() const;

    void setOutdated(bool outdated);
    bool isOutdated() const;

    void setModified(qint64 modified);
    qint64 modified() const;

    Tag &tag();
    Tag &tag() const;

    Cover &cover();
    Cover &cover() const;

    void update();

    bool operator<(const Audio &other) const;
    bool operator>(const Audio &other) const;
    bool operator<=(const Audio &other) const;
    bool operator>=(const Audio &other) const;

    bool operator==(const QString &other) const;
    bool operator==(const Audio &other) const;
    bool operator!=(const QString &other) const;
    bool operator!=(const Audio &other) const;

signals:
    void updated(Audio *audio);

private slots:
    void onTagUpdated();

private:
    File m_file;
    bool m_valid;
    bool m_cached;
    bool m_outdated;
    qint64 m_modified;
    Tag m_tag;
    Cover m_cover;
};

#endif // AUDIO_HPP
