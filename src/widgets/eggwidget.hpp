#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include "barwidget.hpp"
#include "borderlayout.hpp"
#include "constants.hpp"
#include "coverloadercontroller.hpp"
#include "library.hpp"
#include "librarywidget.hpp"
#include "mainwindow.hpp"
#include "types.hpp"

class EggWidget : public MainWindow
{
    Q_OBJECT

public:
    EggWidget(QWidget *parent = nullptr);
    ~EggWidget();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    void setup();
    void setupCss();
    void setupUi();

    BarWidget m_bar;
    LibraryWidget m_library;
};

#endif // EGGWIDGET_HPP
