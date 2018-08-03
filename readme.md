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
- look into compile error for types
- rename `Audio` to `Track`
- prefix static variables with `s_` instead of `_`
- implement operators for `Audio`, used `std::greater<>()` for sorting
- compare current implementation of `lowerBound` with `std::lower_bound` in performance perspective
- variadic template for `log` based on [introduction](http://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/) or multiple arguments
- reserve vector space
- do not allocate `Audio` on heap, consider passing references instead of pointers
- write proper project file
- look into profiling for code optimization, see [profile-guided optimizations](https://docs.microsoft.com/de-de/cpp/build/reference/profile-guided-optimizations)

### C++ Core Guidelines
- [guidelines](https://github.com/isocpp/CppCoreGuidelines)
- use `const` for all not changing variables
- declare functions without member variables as `static`
- do not leak resources
- properly throw and handle exception
- use `shared_pointer` and `unique_pointer` properly
- keep the function argument count low, consider `struct`
- look into polymophism and virtual classes, maybe use for config classes to call `setDefaults` automatically at initialization
- keep functions short and simple with a single operation only
- use `tuple` for multiple return values
- declare time critial functions as `inline`
- pass modifiable parameter as constant reference instead of pointer
- return a constant reference when a copy is undesirable
- single argument constructors need to be `explicit`
- initialize member variables in order of declaration
- properly use initializer / initialization lists `{}`, refer to [SO question](https://stackoverflow.com/questions/18222926/why-is-list-initialization-using-curly-braces-better-than-the-alternatives)
- consider initializing member variables at declaration level
- use parent constructor with `using Parent::Parent` if no own constructor is needed
- properly handle and throw exceptions, refer to [Qt exception safety](http://doc.qt.io/qt-5/exceptionsafety.html)
- use `union` to save memory
- prefer enumerations over macros
- do not make constants all caps
- use `auto` to prevent writing long type names
- always initialize a variable, if they are not default initialized
- initialize variable at first use, not earlier
- wrap complex initialization into lambdas and declare variable `const` if possible
- do not use 'magic constants', e.g. `12` instead of `december`
- move simple computation from run time to compile time, see `constexpr`
- consider using `thread_local` for static variables inside threads
- prefer iterators over range-based for-loop (e.g. `AbstractController::removeObject`, use `erase`instead)

### Player
- move playlist and everything related into own class
- future possibility for `loadFromFile`
- check for better ways to get the current audio after `shuffle` and `unshuffle`

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