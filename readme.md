# egg-player
A Groove Music like music player.

## Roadmap
- [ ] documentation
- [ ] playlist support
- [x] [taglib](https://github.com/taglib/taglib) for tag reading
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [x] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since lastest release
- fix timer pause bug

## Things to do

### Internal
- reactive cache / library
  - use QFileSystemWatcher
  - update library / cache accordingly
- expand thread pool
  - remove threads once finished
  - add function to abort all
- proper mulithreaded library loading
  - look into write-ahead-logging
  - a single LibraryLoaderThread which gets called from the library and emits audios
  - if the audio does it exists it gets pushed into a vector (new vector vs remove)
  - load the missing audios in multiple AudioLoaderThreads and emit them to the LibraryLoaderThread
  - the LibraryLoaderThread inserts them into the cache (use mutex with mutex locker) and emits them
- cache builder thread
  - just use changed audios
- fuzzy library searching
  - store last result, show it if there is no current
- template util functions
- change app background color to black to prevent white flashing when resizing
  - need to use the [windows api](https://forum.qt.io/topic/69867/temporary-white-border-on-resizing-qt-quick-application-window-on-windows-desktop/2)
  - remove background color from css
- create a bass wrapper and use it in the player
  - disable auto looping the current stream
  - try to reinitiate bass after the audio device changed
  - consider using a bass plugin for tag loading instead of taglib
- play around with VA list for logger, just use log as a function, move other function into private namespace
- move font loading into util
- cache as member in music bar
- reformat code properly
- connect app about to quit to pausing bass
- consider renaming globals to common
- prevent negative intervals in timer

### Cosmetic
- do not show certain info at low size
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- color transition in bar