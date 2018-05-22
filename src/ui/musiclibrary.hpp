#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QHeaderView>
#include <QPair>
#include <QScrollBar>
#include <QTableWidget>
#include <QVector>

#include "clickablestyle.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "library.hpp"
#include "rowhoverdelegate.hpp"
#include "utils.hpp"

class MusicLibrary : public QTableWidget
{
    Q_OBJECT

public:
    MusicLibrary(QWidget *parent = nullptr);
    ~MusicLibrary();

    enum SongInfo {Title, Artist, Album, Track, Year, Genre, Length, None};

    void showColumn(SongInfo info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

public slots:
    void insert(Audio *audio, int row = -1);

private:
    QString loadStyleSheet();

    void setup();

    QVector<QPair<SongInfo, Qt::Alignment>> m_columns;
};

#endif // MUSICLIBRARY_HPP
