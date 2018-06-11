#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>

#include "cfgapp.hpp"
#include "cfgbar.hpp"
#include "cfglibrary.hpp"
#include "cfgplayer.hpp"
#include "cfgshortcut.hpp"
#include "constants.hpp"
#include "utils.hpp"

#define cfgApp (Config::instance()->app)
#define cfgBar (Config::instance()->bar)
#define cfgLibrary (Config::instance()->library)
#define cfgPlayer (Config::instance()->player)
#define cfgShortcut (Config::instance()->shortcut)

class Config : QObject
{
public:
    Config(QObject *parent = nullptr);
    ~Config();

    static Config * instance();

    CfgApp app;
    CfgBar bar;
    CfgLibrary library;
    CfgPlayer player;
    CfgShortcut shortcut;

    static Config *_instance;
};

#endif // CONFIG_HPP
