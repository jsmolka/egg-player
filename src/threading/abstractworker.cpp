#include "abstractworker.hpp"

AbstractWorker::AbstractWorker(QObject *parent)
    : QObject(parent)
    , m_interrupted(false)
{

}

AbstractWorker::~AbstractWorker()
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
