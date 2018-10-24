#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "audio.hpp"
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
};

#endif // AUDIOLOADER_HPP
