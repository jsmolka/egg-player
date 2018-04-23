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
    static bool log() const;

    static void setFontSize(double size);
    static double fontSize() const;

    static void setEpLibrary(const QString &path);
    static QString epLibrary() const;

    static void setEpVolume(int volume);
    static int epVolume() const;

    static void setMlSongInfoHeight(int height);
    static int mlSongInfoHeight() const;

    static void setMbHeight(int height);
    static int mbHeight() const;

    static void setMbSpacing(int spacing);
    static int mbSpacing() const;

    static void setMbCoverSize(int size);
    static int mbCoverSize() const;

    static void setMbIconSize(int size);
    static int mbIconSize() const;

    static void setMbTrackLabelWidth(int width);
    static int mbTrackLabelWidth() const;

    static void setMbTimeLabelWidth(int width);
    static int mbTimeLabelWidth() const;

private:
    static QSettings *config;

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
