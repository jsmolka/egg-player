#include "initializer.hpp"

#include <QFileInfo>

#include "core/constants.hpp"
#include "core/cover.hpp"
#include "core/logger.hpp"
#include "core/database/audioitem.hpp"
#include "core/database/coveritem.hpp"
#include "core/database/infoitem.hpp"

void db::Initializer::initialize()
{
    if (!QFileInfo::exists(constants::db::file))
        return init();

    db::InfoItem dbInfo;
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
    db::AudioItem().createTable();
    db::CoverItem().createTable();
    db::InfoItem().createTable();
}

void db::Initializer::initDefaultCover()
{
    db::CoverItem dbCover;
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
    db::InfoItem dbInfo;
    if (!dbInfo.getById(1))
    {
        dbInfo.setId(1);
        dbInfo.setVerion(version());
        dbInfo.insert();
    }
}
