#include "audioloader.hpp"

#include <QApplication>

AudioLoader::AudioLoader(QObject *parent)
    : Callable(parent)
{

}

void AudioLoader::load(const File &file)
{
    Audio *audio = new Audio;
    if (m_dbAudio.getByFile(file))
    {
        m_dbAudio.assignTo(audio);
    }
    else
    {
        audio->setFile(file);
        audio->update();
        if (!audio->isValid())
        {
            delete audio;
            return;
        }
    }
    if (!audio->isCached())
    {
        if (isInterrupted())
            return;

        m_dbAudio.loadFrom(audio);
        m_dbAudio.insert();
    }
    if (audio->isOutdated())
    {
        if (isInterrupted())
            return;

        audio->update();
        audio->cover().invalidate();

        m_dbAudio.loadFrom(audio);
        m_dbAudio.commit();
    }
    if (!audio->cover().isValid())
    {
        if (isInterrupted())
            return;

        const QPixmap cover = Cover::loadFromFile(audio->file());
        m_dbCover.getOrInsertCover(cover);

        m_dbAudio.setCoverId(m_dbCover.id());
        m_dbAudio.commit();
        audio->cover().setId(m_dbCover.id());
    }
    audio->moveToThread(qApp->thread());
    emit loaded(audio);
}
