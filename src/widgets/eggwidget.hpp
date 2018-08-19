#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include "barwidget.hpp"
#include "librarywidget.hpp"
#include "mainwindow.hpp"

class EggWidget : public MainWindow
{
    Q_OBJECT

public:
    explicit EggWidget(QWidget *parent = nullptr);
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
