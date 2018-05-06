#include "librarybuilder.hpp"

LibraryBuilder::LibraryBuilder(Library *library, QObject *parent) :
    QThread(parent)
{
    m_abort = false;
    pm_library = library;

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

LibraryBuilder::~LibraryBuilder()
{

}

void LibraryBuilder::abort()
{
    m_abort = true;
    quit();
    wait();
}

void LibraryBuilder::run()
{
    pm_library->load(Config::Library::path());
}
