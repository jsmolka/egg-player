#ifndef DBINITIALIZER_HPP
#define DBINITIALIZER_HPP

#include "dbclass.hpp"

class DbInitializer : public DbClass
{
public:
    using DbClass::DbClass;

    void initialize();

private:
    bool tableExists(const QString &table);
    void createTables();
    void createTableAudios();
    void createTableCovers();
    void dropTable(const QString &table);

    static constexpr int s_version = 1;
};

#endif // DBINITIALIZER_HPP
