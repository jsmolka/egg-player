#ifndef LIBRARYWIDGET_HPP
#define LIBRARYWIDGET_HPP

#include "widgets/audioswidget.hpp"

class LibraryWidget : public AudiosWidget
{
    Q_OBJECT

public:
    explicit LibraryWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void adjustToWidth(int width);
};

#endif // LIBRARYWIDGET_HPP
