#include "abstractworker.hpp"

AbstractWorker::AbstractWorker(QObject *parent)
    : QObject(parent)
    , m_interrupted(false)
{

}

bool AbstractWorker::isInterrupted() const
{
    return m_interrupted;
}

void AbstractWorker::interrupt()
{
    m_interrupted = true;
}
