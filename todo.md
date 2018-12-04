# Things to do

## General
- properly bind the column in database queries
- explore the benefits of smart pointers and the limits of Qt parenting
- properly forward declare classes, remove unnecessary ones from headers
- explore the benefits of enum classes and flags
- create a base class or a template for pimpl idiom classes
- use NULL in bass
- use public inheritance for singleton
- CurrentState constructor does not need to be explicit
- use qwindows header
- use mutable for member variables in classes
- pass possible deleter for smart pointers
- make FrozenVector a template, possibly rename
- do not use Audio::vector
- use update wrapper in database update functions

### Copy-swap
```cpp
T& T::operator=(const T &rhs) {
  T temp(rhs);
  swap(temp);
  return *this;
}

T& T::operator=(T rhs) {
  swap(rhs);
  return *this
}
```

## Macros
- rename property macros to EGG_PROP_P / C
- remove the macros for getter and setter or make them private
- add property macro for pimple classes (EGG_PROP_P)

## User Interface

### Bar
- use different sliders for volume and duration
  - make the volume slider pop out instead of hiding other icons
  - improve the duration slider style (include some form of hover effect)
  - create a unique handle for the duration slider
- update the track label if the played audio has been modified
- consider splitting into more subclasses
- fade cover through black when changing the audio
- create an AudioFinder class which handles keystrokes
  - create keyReset config field

### Library
- make the scrollbar expandable
- adjust the appearance of library items
  - consider using a less bright white
  - consider using a slightly smaller font size
- add vertical black bars to the library border
- improve smooth scrolling