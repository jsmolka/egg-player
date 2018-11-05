#include "dbinitializer.hpp"

#include <QFileInfo>

#include "core/constants.hpp"
#include "core/cover.hpp"
#include "core/logger.hpp"
#include "core/database/dbaudio.hpp"
#include "core/database/dbcover.hpp"
#include "core/database/dbinfo.hpp"

void db::Initializer::initialize()
{
    if (!QFileInfo::exists(constants::db::file))
        return init();

    db::Info dbInfo;
    if (!dbInfo.getById(1))
        EGG_LOG("Cannot get version of existing database");

    if (dbInfo.version() == version())
        return;

    switch (dbInfo.version())
    {
    }
}

int db::Initializer::version()
{
    return 1;
}

void db::Initializer::init()
{
    initTables();
    initDefaultCover();
    initInfo();
}

void db::Initializer::initTables()
{
    db::Audio().createTable();
    db::Cover().createTable();
    db::Info().createTable();
}

void db::Initializer::initDefaultCover()
{
    db::Cover dbCover;
    if (!dbCover.getById(1))
    {
        const QPixmap cover = ::Cover::scale(QPixmap(constants::img::cover), ::Cover::defaultSize());
        dbCover.setId(1);
        dbCover.setCover(cover);
        dbCover.insert();
    }
}

void db::Initializer::initInfo()
{
    db::Info dbInfo;
    if (!dbInfo.getById(1))
    {
        dbInfo.setId(1);
        dbInfo.setVerion(version());
        dbInfo.insert();
    }
}
