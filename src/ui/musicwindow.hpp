#ifndef MUSICWINDOW_HPP
#define MUSICWINDOW_HPP

#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QScrollBar>

#include "src/constants/constant.hpp"
#include "src/core/library.hpp"
#include "src/ui/components/songinfo.hpp"

class MusicWindow : public QListWidget
{
public:
    MusicWindow(Library *library);

private:
    void setupUi();

    Library *pm_library;
};

#endif // MUSICWINDOW_HPP
