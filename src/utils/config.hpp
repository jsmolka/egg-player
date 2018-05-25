#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <ShellScalingApi.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>
#include <QStandardPaths>

#include "constants.hpp"
#include "utils.hpp"
#include "types.hpp"

class Config
{
public:
    class App
    {
    public:
        static void setFontSize(double size);
        static double fontSize();

        static void setLog(bool log);
        static bool log();
    };

    class Bar
    {
    public:
        static void setGrooveHeight(int height);
        static int grooveHeight();

        static void setHandleSize(int size);
        static int handleSize();

        static void setHeight(int height);
        static int height();

        static void setIconSize(int size);
        static int iconSize();

        static void setMargin(int margin);
        static int margin();

        static void setSpacing(int spacing);
        static int spacing();

        static int coverSize();

        static void setTimeWidth(int width);
        static int timeWidth();

        static void setTrackWidth(int width);
        static int trackWidth();
    };

    class Library
    {
    public:
        static void setCellPadding(int padding);
        static int cellPadding();

        static void setItemHeight(int height);
        static int itemHeight();

        static void setPaths(const StringList &paths);
        static StringList paths();

        static void setScrollBarWidth(int width);
        static int scrollBarWidth();
    };

    class Player
    {
    public:
        static void setLoop(bool loop);
        static bool loop();

        static void setShuffle(bool shuffle);
        static bool shuffle();

        static void setVolume(int volume);
        static int volume();
    };

    class Shortcut
    {
    public:
        static void setNext(const QString &shortcut);
        static QString next();

        static void setPlayPause(const QString &shortcut);
        static QString playPause();

        static void setPrevious(const QString &shortcut);
        static QString previous();

        static void setVolumeDown(const QString &shortcut);
        static QString volumeDown();

        static void setVolumeUp(const QString &shortcut);
        static QString volumeUp();
    };

private:
    static void save();
    static void load();

    static void saveObjects();
    static void loadObjects();

    static QJsonDocument json();
    static QJsonObject & app();
    static QJsonObject & bar();
    static QJsonObject & library();
    static QJsonObject & player();
    static QJsonObject & shortcut();

    static void setValue(QJsonObject &object, const QString &key, const QJsonValue &value);
    static void setValue(QJsonObject &object, const QString &key, const QJsonArray &value);

    static void setDefault(QJsonObject &object, const QString &key, const QJsonValue &value);
    static void setDefault(QJsonObject &object, const QString &key, const QJsonArray &value);
    static void setDefaults();

    static float scale(float value);
    static int scale(int value);

    static int makeEven(int value);

    static QJsonDocument _json;
    static QJsonObject _app;
    static QJsonObject _bar;
    static QJsonObject _library;
    static QJsonObject _player;
    static QJsonObject _shortcut;
};

#endif // CONFIG_HPP
