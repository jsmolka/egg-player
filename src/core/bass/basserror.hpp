#ifndef BASS_BASSERROR_HPP
#define BASS_BASSERROR_HPP

namespace bass
{

class BassError
{
public:
    static bool check(bool value);

private:
    static void error();
};

}

#endif // BASS_BASSERROR_HPP
