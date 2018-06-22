#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QHeaderView>
#include <QVector>

#include "config.hpp"
#include "constants.hpp"
#include "library.hpp"
#include "tablewidget.hpp"
#include "util.hpp"

class MusicLibrary : public TableWidget
{
    Q_OBJECT

public:
    MusicLibrary(QWidget *parent = nullptr);
    ~MusicLibrary();

    enum SongInfo {None, Title, Artist, Album, Track, Year, Genre, Length};

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

    QVector<Column> m_columns;
};

#endif // MUSICLIBRARY_HPP
