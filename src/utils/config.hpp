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

    static void ALog(bool log);
    static bool ALog();

    static void AFontSize(double size);
    static double AFontSize();

    static void SPlayPause(const QString &shortcut);
    static QString SPlayPause();

    static void SNext(const QString &shortcut);
    static QString SNext();

    static void SPrevious(const QString &shortcut);
    static QString SPrevious();

    static void SVolumeUp(const QString &shortcut);
    static QString SVolumeUp();

    static void SVolumeDown(const QString &shortcut);
    static QString SVolumeDown();

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
    static bool sectionContains(const QString &section, const QString &key);

    static QSettings *config;

    static const QString kApp;
    static const QString kShortcut;
    static const QString kPlayer;
    static const QString kLibrary;
    static const QString kBar;

    static const QString kALog;
    static const QString kAFontSize;
    static const QString kSPlayPause;
    static const QString kSNext;
    static const QString kSPrevious;
    static const QString kSVolumeUp;
    static const QString kSVolumeDown;
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
    static const QString dSPlayPause;
    static const QString dSNext;
    static const QString dSPrevious;
    static const QString dSVolumeUp;
    static const QString dSVolumeDown;
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
