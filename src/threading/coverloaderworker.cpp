#include "coverloaderworker.hpp"

CoverLoaderWorker::CoverLoaderWorker(QObject *parent)
    : CoverLoaderWorker(Audios(), parent)
{

}

CoverLoaderWorker::CoverLoaderWorker(const Audios &audios, QObject *parent)
    : AbstractThread(parent)
    , m_audios(audios)
{

}

CoverLoaderWorker::~CoverLoaderWorker()
{

}

void CoverLoaderWorker::setAudios(const Audios &audios)
{
    m_audios = audios;
}

Audios CoverLoaderWorker::audios() const
{
    return m_audios;
}

void CoverLoaderWorker::run()
{
    for (Audio *audio : m_audios)
    {
        if (isAbort())
            return;

        if (audio->coverId() == -1)
            emit loaded(audio, audio->cover());
    }
}
