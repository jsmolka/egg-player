#ifndef DB_INITIALIZER_HPP
#define DB_INITIALIZER_HPP

namespace db
{

class Initializer
{
public:
    static void initialize();

private:
    static int version();

    static void init();
    static void initTables();
    static void initDefaultCover();
    static void initInfo();
};

}

#endif // DB_INITIALIZER_HPP
