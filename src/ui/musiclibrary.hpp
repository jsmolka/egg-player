#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidget>
#include <QVector>

#include "clickablestyle.hpp"
#include "constants.hpp"
#include "config.hpp"
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
    struct ColumnInfo
    {
        ColumnInfo(SongInfo info = None, Qt::Alignment alignment = Qt::AlignLeft, bool expand = true)
        {
            this->info = info;
            this->alignment = alignment;
            this->expand = expand;
        }

        SongInfo info;
        Qt::Alignment alignment;
        bool expand;
    };

    QString loadStyleSheet();

    void setup();

    QVector<ColumnInfo> m_columns;
};

#endif // MUSICLIBRARY_HPP
