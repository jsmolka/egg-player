#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "types.hpp"

class AudioLoader : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoader(QObject *parent = nullptr);
    AudioLoader(const StringList &files, QObject *parent = nullptr);
    ~AudioLoader();

    void setFiles(const StringList &files);

signals:
    void loaded(Audio *);

protected:
    void run() override;

private:
    StringList m_files;
};

#endif // AUDIOLOADER_HPP
