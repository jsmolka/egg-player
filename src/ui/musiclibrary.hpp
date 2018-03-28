#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include <QListWidget>
#include <QScrollBar>

#include "src/constants/constant.hpp"
#include "src/core/library.hpp"
#include "src/ui/components/songinfo.hpp"

class MusicLibrary : public QListWidget
{
public:
    MusicLibrary(Library *library, QWidget *parent = 0);
    ~MusicLibrary();

private:
    void setupUi();

    Library *pm_library;
};

#endif // MUSICLIBRARY_HPP
