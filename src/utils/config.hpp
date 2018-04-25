#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QApplication>
#include <QSettings>
#include <QStandardPaths>

#include "constants.hpp"

/*
 * The Config class manages all user editable settings
 * and is globally available in form of static functions.
 * Those have a special nameing scheme and are a combination
 * of the capital letter of the section and the key.
 * Notice that getters and setter have a same name, start with
 * a capital letter and just differ in having a parameter or not.
 */
class Config
{
public:
    static void create();
    static bool contains(const QString &key);

    static void ALog(bool log);
    static bool ALog();

    static void AFontSize(double size);
    static double AFontSize();

    static void PVolume(int volume);
    static int PVolume();

    static void PShuffle(bool shuffle);
    static bool PShuffle();

    static void PLoop(bool loop);
    static bool PLoop();

    static void LPath(const QString &path);
    static QString LPath();

    static void LItemHeight(int height);
    static int LItemHeight();

    static void BHeight(int height);
    static int BHeight();

    static void BSpacing(int spacing);
    static int BSpacing();

    static void BCoverSize(int size);
    static int BCoverSize();

    static void BIconSize(int size);
    static int BIconSize();

    static void BTrackWidth(int width);
    static int BTrackWidth();

    static void BTimeWidth(int width);
    static int BTimeWidth();

private:
    static QSettings *config;

    static const QString kALog;
    static const QString kAFontSize;
    static const QString kPVolume;
    static const QString kPShuffle;
    static const QString kPLoop;
    static const QString kLPath;
    static const QString kLItemHeight;
    static const QString kBHeight;
    static const QString kBSpacing;
    static const QString kBCoverSize;
    static const QString kBIconSize;
    static const QString kBTrackWidth;
    static const QString kBTimeWidth;

    static const bool dALog;
    static const double dAFontSize;
    static const int dPVolume;
    static const bool dPShuffle;
    static const bool dPLoop;
    static const QString dLPath;
    static const int dLItemHeight;
    static const int dBHeight;
    static const int dBSpacing;
    static const int dBCoverSize;
    static const int dBIconSize;
    static const int dBTrackWidth;
    static const int dBTimeWidth;
};

#endif // CONFIG_HPP
