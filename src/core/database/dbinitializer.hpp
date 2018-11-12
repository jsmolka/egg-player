#ifndef DB_DBINITIALIZER_HPP
#define DB_DBINITIALIZER_HPP

namespace db
{

class DbInitializer
{
public:
    static void init();

private:
    static int version();

    static void initTables();
    static void initDefaultCover();
    static void initInfo();

    static void update();
};

}

#endif // DB_DBINITIALIZER_HPP
