#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include <QSettings>
#include <QWidget>

#include "borderlayout.hpp"
#include "constants.hpp"
#include "library.hpp"
#include "librarywidget.hpp"
#include "barwidget.hpp"

class EggWidget : public QWidget
{
    Q_OBJECT

public:
    EggWidget(QWidget *parent = nullptr);
    ~EggWidget();

    void showSavedPosition();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onMusicLibraryDoubleClicked(const QModelIndex &index);

private:
    void setup();
    void setupUi();

    void savePosition();

    LibraryWidget m_libraryWidget;
    BarWidget m_barWidget;
};

#endif // EGGWIDGET_HPP
