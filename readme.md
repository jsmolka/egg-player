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
- [x] reactive cache

## Changes since lastest release
- add reactive cache
- significantly improve audio caching
- significantly improve cover caching 
- change icon hover style

## Things to do

### General
- look into compile error in `types.hpp`
- write proper project file, use compiler optimization
- test jpg instead of png for cover conversion
- space after tables in create tables
- make PlaylistItem private
- SongInfo to AudioInfo

### File System
- create own `FileSystem` class
- detect insert, remove, modify, rename
- consider using `QHash<path, filesize>`

### Live changes
- create `Audios` class an forward necessary vector functions
    - signal `inserted`, called at `insert` / `append`
    - signal `removed`, called at `removed`
    - signal `updated`, forwared from `Audio`
        - make `Audio` a `QObject` at emit signal at update to handle changes
- use pointer to this class / object in player and playlist
- connect `Audios` signals to class when updating is needed
- keep a list of shuffled indices in `Playlist` ([example](https://stackoverflow.com/a/16968081/7057528))
    - shuffle indices
    - create new indices at `sort`

```python
# Default state, sorted
i = [0,  1,  2]
a = [a0, a1, a2]

# Shuffled state
i = [2,  0,  1]
a = [a0, a1, a2]

# Remove item at index 2
index = 2
i = [2,  0]  # -> [1, 0]
a = [a0, a1]
for x, idx in enumerate(i):
    if x >= index:
        i[idx] -= 1
```

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
- prefer iterators over range-based for-loop
- minimize singleton usage
- use [Qt algorithms](http://doc.qt.io/qt-5/qtalgorithms.html)
- use [std algorithms](http://www.cplusplus.com/reference/algorithm/)
- std::sort with qLess<T>
- probably useful
    - [insert binary](https://stackoverflow.com/a/25524075/7057528)
    - [binary predicate](https://stackoverflow.com/a/4269392/7057528)
    - [array insert end](https://stackoverflow.com/a/5961066/7057528)

### Reactive cache
- use `QFileSystemWatcher`
- detect live changes and update library accordingly
  
### User interface
- do not show certain info at low size
- fuzzy library searching
- [expand scrollbar](https://stackoverflow.com/a/23677355/7057528)
- [scrollable text](https://stackoverflow.com/a/10655396/7057528)