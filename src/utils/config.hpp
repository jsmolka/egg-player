#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>
#include <QStandardPaths>

#include "constants.hpp"
#include "utils.hpp"

class Config
{
public:
    static void create();

    class App
    {
    public:
        static void create();

        static void setFontSize(double size);
        static double fontSize();

        static void setLog(bool log);
        static bool log();

    private:
        static void setDefault(const QString &key, const QJsonValue &value);
        static void setValue(const QString &key, const QJsonValue &value);

        static const QString kFontSize;
        static const QString kLog;

        static const double dFontSize;
        static const bool dLog;
    };

    class Bar
    {
    public:
        static void create();

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

    private:
        static void setDefault(const QString &key, const QJsonValue &value);
        static void setValue(const QString &key, const QJsonValue &value);

        static const QString kHeight;
        static const QString kIconSize;
        static const QString kMargin;
        static const QString kSpacing;
        static const QString kTimeWidth;
        static const QString kTrackWidth;


        static const int dHeight;
        static const int dIconSize;
        static const int dMargin;
        static const int dSpacing;
        static const int dTimeWidth;
        static const int dTrackWidth;
    };

    class Library
    {
    public:
        static void create();

        static void setItemHeight(int height);
        static int itemHeight();

        static void setPaths(const QStringList &paths);
        static QStringList paths();

    private:
        static void setDefault(const QString &key, const QJsonValue &value);
        static void setDefault(const QString &key, const QJsonArray &value);
        static void setValue(const QString &key, const QJsonValue &value);
        static void setValue(const QString &key, const QJsonArray &value);

        static const QString kItemHeight;
        static const QString kPaths;

        static const int dItemHeight;
        static const QJsonArray dPaths;
    };

    class Player
    {
    public:
        static void create();

        static void setLoop(bool loop);
        static bool loop();

        static void setShuffle(bool shuffle);
        static bool shuffle();

        static void setVolume(int volume);
        static int volume();

    private:
        static void setDefault(const QString &key, const QJsonValue &value);
        static void setValue(const QString &key, const QJsonValue &value);

        static const QString kLoop;
        static const QString kShuffle;
        static const QString kVolume;

        static const bool dLoop;
        static const bool dShuffle;
        static const int dVolume;

    };

    class Shortcut
    {
    public:
        static void create();

        static void setNext(const QString &oShortcut);
        static QString next();

        static void setPlayPause(const QString &oShortcut);
        static QString playPause();

        static void setPrevious(const QString &oShortcut);
        static QString previous();

        static void setVolumeDown(const QString &oShortcut);
        static QString volumeDown();

        static void setVolumeUp(const QString &oShortcut);
        static QString volumeUp();

    private:
        static void setDefault(const QString &key, const QJsonValue &value);
        static void setValue(const QString &key, const QJsonValue &value);

        static const QString kNext;
        static const QString kPlayPause;
        static const QString kPrevious;
        static const QString kVolumeDown;
        static const QString kVolumeUp;

        static const QString dNext;
        static const QString dPlayPause;
        static const QString dPrevious;
        static const QString dVolumeDown;
        static const QString dVolumeUp;
    };

private:
    static void save();
    static void load();

    static QJsonDocument jDocument;
    static QJsonObject jObject;

    static QJsonObject oApp;
    static QJsonObject oBar;
    static QJsonObject oLibrary;
    static QJsonObject oPlayer;
    static QJsonObject oShortcut;

    static const QString kApp;
    static const QString kBar;
    static const QString kLibrary;
    static const QString kPlayer;
    static const QString kShortcut;
};

#endif // CONFIG_HPP
