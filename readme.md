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
- significantly improve audio caching 
- significantly improve cover caching 
- change icon hover style

## Things to do

### General
- rewrite `LibraryWidget`
- `QKeySequence` for `Shortcut`
- proper template function implementation for `chunk`
- look into compile error for types
- rename `Audio` to `Track`
- use `explicit` constructors
- prefix static variables with `_s` instead of `_`

### C++ Core Guidelines
- [guidelines](https://github.com/isocpp/CppCoreGuidelines)
- use `const` for all not changing variables

### Utils
- use `inline` functions for `Utils`
- move css loading to its widget
- move font loading from `Utils` to `main`

### Icons
- use svg format / different sizes

### Reactive cache
- use `QFileSystemWatcher`
- update `Library`, `Audio` accordingly
- store `lastModified.toSecsSinceEpoch()` in database
- compare cached result with current result during loading
- reload and update if unequal

### Windows util
- create a windows util
- use defines to make it cross platform compatible
- change app background color to black to prevent white flashing when resizing
  - need to use the [windows api](https://forum.qt.io/topic/69867/temporary-white-border-on-resizing-qt-quick-application-window-on-windows-desktop/2)
  - remove background color from css
- move scale functions into this util
- move register hotkey functions into this util
  
### User interface
- do not show certain info at low size
- fuzzy library searching
- [expand scrollbar](https://stackoverflow.com/a/23677355/7057528)
- [scrollable text](https://stackoverflow.com/a/10655396/7057528)
- [color transition](https://stackoverflow.com/a/34445886/7057528)