#ifndef LIBRARYBUILDER_HPP
#define LIBRARYBUILDER_HPP

#include <QApplication>
#include <QThread>

#include "library.hpp"

class LibraryBuilder : public QThread
{
    Q_OBJECT

public:
    LibraryBuilder(Library *library, QObject *parent = nullptr);
    ~LibraryBuilder();

public slots:
    void abort();

protected:
    void run() override;

private:
    bool m_abort;
    Library *pm_library;
};

#endif // LIBRARYBUILDER_HPP
