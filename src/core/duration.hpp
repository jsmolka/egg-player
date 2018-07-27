#ifndef DURATION_HPP
#define DURATION_HPP

#include <QString>
#include <QTime>

class Duration
{
public:
    Duration();
    Duration(int secs);
    ~Duration();

    int secs() const;

    QString toString() const;

private:
    int m_secs;
};

#endif // DURATION_HPP
