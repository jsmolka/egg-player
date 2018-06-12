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
- move library into music library (at least an option)
- adjust bar to config changes
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
- fuzzy library searching
  - store last result, show it if there is no current
- completely rewrite documentation before next release
  - place the docstrings in the header instead of the source file
```cpp
/*!
 * Describe what the function does rather than
 * listing all arguments. Explain possible unclear
 * things / variable names.
 */
int Class::function(int a, double t);
```
- rename the widgets
- [namespace](https://stackoverflow.com/a/10493005/7057528) instead of class for utils
  - use templates for functions
  - time from milliseconds (do not split it up before)
- change app background color to black to prevent white flashing when resizing
- change dir structure
  - core
    - threading
  - globals
  - utils
    - config
  - widgets
    - components
    - layouts
- create a bass wrapper and use it in the player

### Cosmetic
- do not show certain info at low size
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- color transition in bar