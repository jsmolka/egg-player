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

    InfoItem intoItem;
    if (!intoItem.getById(1))
        EGG_LOG("Cannot get version of existing database");

    if (intoItem.version() == version())
        return;

    switch (intoItem.version())
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
    AudioItem().createTable();
    CoverItem().createTable();
    InfoItem().createTable();
}

void db::Initializer::initDefaultCover()
{
    CoverItem coverItem;
    if (!coverItem.getById(1))
    {
        const QPixmap cover = ::Cover::scale(QPixmap(constants::img::cover), ::Cover::defaultSize());
        coverItem.setId(1);
        coverItem.setCover(cover);
        coverItem.insert();
    }
}

void db::Initializer::initInfo()
{
    InfoItem infoItem;
    if (!infoItem.getById(1))
    {
        infoItem.setId(1);
        infoItem.setVerion(version());
        infoItem.insert();
    }
}
