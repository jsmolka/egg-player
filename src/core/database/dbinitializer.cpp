#include "dbinitializer.hpp"

#include <QFileInfo>

#include "core/constants.hpp"
#include "core/cover.hpp"
#include "core/logger.hpp"
#include "core/database/audioitem.hpp"
#include "core/database/coveritem.hpp"
#include "core/database/infoitem.hpp"

void db::DbInitializer::init()
{
    if (!QFileInfo::exists(constants::db::File))
    {
        initTables();
        initDefaultCover();
        initInfo();
    }
    else
    {
        update();
    }
}

int db::DbInitializer::version()
{
    return 1;
}

void db::DbInitializer::initTables()
{
    AudioItem().createTable();
    CoverItem().createTable();
    InfoItem().createTable();
}

void db::DbInitializer::initDefaultCover()
{
    CoverItem coverItem;
    if (!coverItem.getById(1))
    {
        const QPixmap cover = ::Cover::scale(QPixmap(constants::img::Cover), ::Cover::defaultSize());
        coverItem.setId(1);
        coverItem.setCover(cover);
        coverItem.insert();
    }
}

void db::DbInitializer::initInfo()
{
    InfoItem infoItem;
    if (!infoItem.getById(1))
    {
        infoItem.setId(1);
        infoItem.setVersion(version());
        infoItem.insert();
    }
}

void db::DbInitializer::update()
{
    InfoItem infoItem;
    if (!infoItem.getById(1))
        egg_log() << "Cannot get version of existing database";

    if (infoItem.version() == version())
        return;
}
