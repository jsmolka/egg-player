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

enum SongInfo {None, Title, Artist, Album, Track, Year, Genre, Length};

class MusicLibrary : public QTableWidget
{
    Q_OBJECT

public:
    MusicLibrary(QWidget *parent = nullptr);
    ~MusicLibrary();

    void addColumn(SongInfo info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

public slots:
    void insert(Audio *audio, int row = -1);

private:
    struct Column
    {
        Column(SongInfo info = SongInfo::None, Qt::Alignment alignment = 0) :
            info(info), alignment(alignment) {}

        SongInfo info;
        Qt::Alignment alignment;
    };

    void loadCss();
    void setup();

    QString audioText(Audio *audio, int column);

    Library *pm_library;
    QVector<Column> m_columns;
};

#endif // MUSICLIBRARY_HPP
