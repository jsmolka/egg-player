#ifndef BASS_ERROR_HPP
#define BASS_ERROR_HPP

namespace bass
{

class Error
{
protected:
    static bool check(bool value);

private:
    static void error();
};

}

#endif // BASS_ERROR_HPP
