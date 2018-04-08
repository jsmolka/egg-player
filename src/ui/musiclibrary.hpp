#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QListWidget>
#include <QScrollBar>

#include "constant.hpp"
#include "library.hpp"
#include "songinfo.hpp"

class MusicLibrary : public QListWidget
{
    Q_OBJECT

public:
    MusicLibrary(Library *library, QWidget *parent = 0);
    ~MusicLibrary();

private:
    void setupUi();

    Library *pm_library;
};

#endif // MUSICLIBRARY_HPP
