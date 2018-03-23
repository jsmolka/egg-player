#ifndef SONGLIST_HPP
#define SONGLIST_HPP

#include <QLabel>
#include <QListWidget>

#include "src/core/library.hpp"

class SongList : public QListWidget
{
public:
    SongList(Library *library);

private:
    void setupUi();

    Library *pm_library;
};

#endif // SONGLIST_HPP
