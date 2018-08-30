#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "audio.hpp"
#include "cache.hpp"
#include "callable.hpp"
#include "types.hpp"

class AudioLoader : public Callable
{
    Q_OBJECT

public:
    explicit AudioLoader(QObject *parent = nullptr);

public slots:
    void load(const File &file);

signals:
    void loaded(Audio *audio);

private:
    Cache m_cache;
};

#endif // AUDIOLOADER_HPP
