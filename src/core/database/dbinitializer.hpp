#ifndef DBINITIALIZER_HPP
#define DBINITIALIZER_HPP

#include "dbbase.hpp"
#include "globals.hpp"

class DbInitializer : public DbBase
{
public:
    using DbBase::DbBase;

    void initialize();

private:
    bool tableExists(const QString &table);
    void createTables();
    void createTableAudios();
    void createTableCovers();
    void dropTable(const QString &table);

    void insertDefaultCover();

    static constexpr int s_version = 1;
};

#endif // DBINITIALIZER_HPP
