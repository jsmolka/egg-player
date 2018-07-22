#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include "barwidget.hpp"
#include "borderlayout.hpp"
#include "constants.hpp"
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

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    void setup();
    void setupUi();

    LibraryWidget m_library;
    BarWidget m_bar;
};

#endif // EGGWIDGET_HPP
