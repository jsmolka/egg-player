#include "abstractworker.hpp"

AbstractWorker::AbstractWorker(QObject *parent)
    : QObject(parent)
    , m_interrupt(false)
{

}

AbstractWorker::~AbstractWorker()
{

}

bool AbstractWorker::isInterrupt() const
{
    return m_interrupt;
}

void AbstractWorker::interrupt()
{
    m_interrupt = true;
}
