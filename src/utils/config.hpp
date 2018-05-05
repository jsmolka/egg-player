#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QApplication>
#include <QSettings>
#include <QStandardPaths>

#include "constants.hpp"

class Config
{
public:
    static void create();

    class App
    {
    public:
        static void create();
        static bool contains(const QString &key);

        static void setLog(bool log);
        static bool log();

        static void setFontSize(double size);
        static double fontSize();

    private:
        static const QString kApp;

        static const QString kLog;
        static const QString kFontSize;

        static const bool dLog;
        static const double dFontSize;
    };

    class Shortcut
    {
    public:
        static void create();
        static bool contains(const QString &key);

        static void setPlayPause(const QString &shortcut);
        static QString playPause();

        static void setNext(const QString &shortcut);
        static QString next();

        static void setPrevious(const QString &shortcut);
        static QString previous();

        static void setVolumeUp(const QString &shortcut);
        static QString volumeUp();

        static void setVolumeDown(const QString &shortcut);
        static QString volumeDown();

    private:
        static const QString kShortcut;

        static const QString kPlayPause;
        static const QString kNext;
        static const QString kPrevious;
        static const QString kVolumeUp;
        static const QString kVolumeDown;

        static const QString dPlayPause;
        static const QString dNext;
        static const QString dPrevious;
        static const QString dVolumeUp;
        static const QString dVolumeDown;
    };

    class Player
    {
    public:
        static void create();
        static bool contains(const QString &key);

        static void setVolume(int volume);
        static int volume();

        static void setShuffle(bool shuffle);
        static bool shuffle();

        static void setLoop(bool loop);
        static bool loop();

    private:
        static const QString kPlayer;

        static const QString kVolume;
        static const QString kShuffle;
        static const QString kLoop;

        static const int dVolume;
        static const bool dShuffle;
        static const bool dLoop;
    };

    class Library
    {
    public:
        static void create();
        static bool contains(const QString &key);

        static void setPath(const QString &path);
        static QString path();

        static void setItemHeight(int height);
        static int itemHeight();

    private:
        static const QString kLibrary;

        static const QString kPath;
        static const QString kItemHeight;

        static const QString dPath;
        static const int dItemHeight;
    };

    class Bar
    {
    public:
        static void create();
        static bool contains(const QString &key);

        static void setHeight(int height);
        static int height();

        static void setMargin(int margin);
        static int margin();

        static void setSpacing(int spacing);
        static int spacing();

        static int coverSize();

        static void setIconSize(int size);
        static int iconSize();

        static void setTrackWidth(int width);
        static int trackWidth();

        static void setTimeWidth(int width);
        static int timeWidth();

    private:
        static const QString kBar;

        static const QString kHeight;
        static const QString kSpacing;
        static const QString kMargin;
        static const QString kIconSize;
        static const QString kTrackWidth;
        static const QString kTimeWidth;

        static const int dHeight;
        static const int dSpacing;
        static const int dMargin;
        static const int dIconSize;
        static const int dTrackWidth;
        static const int dTimeWidth;
    };

private:
    static bool contains(const QString &group, const QString &key);
    static void setValue(const QString &group, const QString &key, const QVariant &value);
    static QVariant value(const QString &group, const QString &key, const QVariant &defaultValue);

    static QSettings *config;
};

#endif // CONFIG_HPP
