#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include <QMimeData>

#include "core/globals.hpp"
#include "widgets/barwidget.hpp"
#include "widgets/librarywidget.hpp"
#include "widgets/parts/mainwindow.hpp"

class EggWidget : public MainWindow
{
    Q_OBJECT    

public:
    explicit EggWidget(QWidget *parent = nullptr);

    EGG_PPROP(BarWidget *, bar, setBar, bar)
    EGG_PPROP(LibraryWidget *, library, setLibrary, library)

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    QStrings processDropEvent(const QMimeData *data);

    void setup();
    void setupCss();
    void setupUi();
};

#endif // EGGWIDGET_HPP
