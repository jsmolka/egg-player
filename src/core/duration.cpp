#include "duration.hpp"

#include <QTime>

Duration::Duration()
    : Duration(0)
{

}

Duration::Duration(int secs)
    : m_secs(secs)

{

}

void Duration::setSecs(int secs)
{
    m_secs = secs;
}

int Duration::secs() const
{
    return m_secs;
}

QString Duration::toString() const
{
    const QTime time = QTime(0, 0).addSecs(m_secs);

    if (m_secs < 600)
        return time.toString("m:ss");
    if (m_secs < 3600)
        return time.toString("mm:ss");
    if (m_secs < 36000)
        return time.toString("h:mm:ss");

    return time.toString("hh:mm:ss");
}
