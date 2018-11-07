#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include <QMimeData>

#include "core/types.hpp"
#include "widgets/barwidget.hpp"
#include "widgets/librarywidget.hpp"
#include "widgets/parts/mainwindow.hpp"

class EggWidget : public MainWindow
{
    Q_OBJECT    

public:
    explicit EggWidget(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index);

private:
    QStrings processDropEvent(const QMimeData *data);
    void processDropEventFile(QStrings &files, const QString &file);
    void processDropEventDir(QStrings &files, const QString &path);

    void init();
    void initUi();
    void initStyle();

    BarWidget m_bar;
    LibraryWidget m_library;
};

#endif // EGGWIDGET_HPP
