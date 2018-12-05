#include "audiofinder.hpp"

#include <QApplication>

AudioFinder::AudioFinder(QObject *parent)
    : QObject(parent)
    , m_audios(nullptr)
    , m_reset(this)
    , m_index(0)
{
    connect(&m_reset, &QTimer::timeout, this, &AudioFinder::reset);

    m_reset.setSingleShot(true);
}

void AudioFinder::setAudios(Audios *audios)
{
    m_audios = audios;
}

void AudioFinder::addKey(const QString &key)
{
    m_string.append(key);

    m_reset.start(qApp->keyboardInputInterval());
}

int AudioFinder::search()
{
    if (!m_audios || m_index == -1 || m_string.isEmpty())
        return -1;

    for ( ; m_index < m_audios->size(); ++m_index)
    {
        const Audio audio = m_audios->at(m_index);
        if (audio.tag().title().startsWith(m_string, Qt::CaseInsensitive))
            return m_index;
    }
    m_index = -1;

    return m_index;
}

void AudioFinder::reset()
{
    m_string = QString();
    m_index = 0;
}
