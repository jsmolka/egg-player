#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QApplication>
#include <QSettings>

#include "constants.hpp"

class Config
{
public:
    static void load();

    static bool contains(const QString &key);

    static void setEggPlayerLibrary(const QString &string);
    static QString eggPlayerLibrary();

    static void setEggPlayerVolume(int volume);
    static int eggPlayerVolume();

    static void setMusicBarHeight(int height);
    static int musicBarHeight();

    static void setMusicBarSpacing(int spacing);
    static int musicBarSpacing();
};

#endif // CONFIG_HPP
