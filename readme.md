# egg-player
A Groove Music like music player.

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [x] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since lastest release

## Things to do

### Internal
- use the e-prefix for all global variables instead of egg
- duration instead of length in Audio and other classes
- check for the max property in timer pause
- consider loading covers with multiple threads
- move library into music library
- rework config
  - load the config once and save it when the object gets destroyed
  - rework the players volume part in the music bar accordingly
  - inherit from QObject to destroy on application closing (maybe set the parent later)
  - create one global instance and define the fields `cfgApp.log()`
- rework logger
  - use a [message handler](https://stackoverflow.com/a/4954188/7057528) which opens a text stream
  - write a function which wraps around `qInfo`, define it like `gLog(msg, ...)`
  - use [cstdarg](https://en.wikipedia.org/wiki/Stdarg.h#.3Cvarargs.h.3E) to process arguments
  - use a static variable which holds the value of `Config::App::log`
- reactive cache / library
  - store file size in cache
  - update audio if size changed
  - use QFileSystemWatcher
  - update library / cache accordingly
- expand thread pool
  - remove threads once finished
  - add function to abort all
- cache transaction (important)
  - start in constructor
  - commit in destructor
  - use member query
  - use member database
  - pass a flag for read only to prevent creating a transaction
- proper mulithreaded library loading
  - look into write-ahead-logging
  - a single LibraryLoaderThread which gets called from the library and emits audios
  - if the audio does it exists it gets pushed into a vector (new vector vs remove)
  - load the missing audios in multiple AudioLoaderThreads and emit them to the LibraryLoaderThread
  - the LibraryLoaderThread inserts them into the cache (use mutex with mutex locker) and emits them
- search the library by typing
  - search based on sorted
  - store last result, show it if there is no current
  - reset search string after certain time

### Cosmetic
- do not show certain info at low size
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- color transition in bar