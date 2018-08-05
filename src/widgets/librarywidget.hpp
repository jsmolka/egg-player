#ifndef LIBRARYWIDGET_HPP
#define LIBRARYWIDGET_HPP

#include <QHeaderView>
#include <QVector>

#include "audio.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "library.hpp"
#include "tablewidget.hpp"

class LibraryWidget : public TableWidget
{
    Q_OBJECT

public:
    LibraryWidget(QWidget *parent = nullptr);
    ~LibraryWidget();

    enum SongInfo {None, Title, Artist, Album, Track, Year, Genre, Duration};

    void setLibrary(Library *library);
    void removeLibrary();

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

    void setup();
    void setupCss();

    QString audioText(Audio *audio, int column);

    Library *m_library;
    QVector<Column> m_columns;
};

#endif // LIBRARYWIDGET_HPP
