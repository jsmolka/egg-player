#ifndef BASSERROR_HPP
#define BASSERROR_HPP

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

#endif // BASSERROR_HPP
