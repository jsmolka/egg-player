#ifndef DURATION_HPP
#define DURATION_HPP

#include <QString>

class Duration
{
public:
    Duration();
    explicit Duration(int secs);

    void setSecs(int secs);
    int secs() const;

    QString toString() const;

private:
    int m_secs;
};

#endif // DURATION_HPP
