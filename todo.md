# Things to do

## General
- write proper project file, use compiler optimization
- make PlaylistItem private
- SongInfo to AudioInfo
- QSet vs QVector for files in Directory
- [utilize string better](https://wiki.qt.io/Using_QString_Effectively)
- update qt creator
- [use clang features](http://blog.qt.io/blog/2018/07/18/qt-creator-4-7-0-released/)

## Threading
- possibly rewrite threading
- create a threadpool to recycle threads
- try using multiple workers per thread
- create an easy abstract class to run objects in threads

## C++ Core Guidelines
- [guidelines](https://github.com/isocpp/CppCoreGuidelines)
- use `const` for all not changing variables
- declare functions without member variables as `static`
- do not leak resources
- properly throw and handle exception
- use [smart pointers](https://stackoverflow.com/a/5026705), `shared_pointer` and `unique_pointer` properly
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
  
## User interface
- do not show certain info at low size
- fuzzy library searching
- [expand scrollbar](https://stackoverflow.com/a/23677355/7057528)
- [scrollable text](https://stackoverflow.com/a/10655396/7057528)

## Possible future changes
- do not cache loaded covers, calculate dominant color right after first load and store for id
- test jpg instead of png for cover caching