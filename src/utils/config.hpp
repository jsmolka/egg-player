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

    static bool contains(const QString &key);

    static void setLog(bool log);
    static bool log();

    static void setFontSize(double size);
    static double fontSize();

    static void setEpLibrary(const QString &string);
    static QString epLibrary();

    static void setEpVolume(int volume);
    static int epVolume();

    static void setMlSongInfoHeight(int height);
    static int mlSongInfoHeight();

    static void setMbHeight(int height);
    static int mbHeight();

    static void setMbSpacing(int spacing);
    static int mbSpacing();

    static void setMbCoverSize(int size);
    static int mbCoverSize();

    static void setMbIconSize(int size);
    static int mbIconSize();

    static void setMbTrackLabelWidth(int width);
    static int mbTrackLabelWidth();

    static void setMbTimeLabelWidth(int width);
    static int mbTimeLabelWidth();

private:
    static const QString kLog;
    static const QString kFontSize;
    static const QString kEpLibrary;
    static const QString kEpVolume;
    static const QString kMlSongInfoHeight;
    static const QString kMbHeight;
    static const QString kMbSpacing;
    static const QString kMbCoverSize;
    static const QString kMbIconSize;
    static const QString kMbTrackLabelWidth;
    static const QString kMbTimeLabelWidth;

    static const bool dLog;
    static const double dFontSize;
    static const QString dEpLibrary;
    static const int dEpVolume;
    static const int dMlSongInfoHeight;
    static const int dMbHeight;
    static const int dMbSpacing;
    static const int dMbCoverSize;
    static const int dMbIconSize;
    static const int dMbTrackLabelWidth;
    static const int dMbTimeLabelWidth;
};

#endif // CONFIG_HPP
