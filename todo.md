# Things to do

## Rework
- proper query binding in database queries
- prevent filesystem from crashing when adding lots of files
- rework / improve tablewidgets
- add config option to disable smooth scrolling
- before release: check / improve all classes
- remove qobject macro from objects without signals / slots

## User Interface
### Bar
- use different sliders for volume and duration and volume
  - make the volume slider pop out instead of hiding other icons
  - improve the duration slider style (include some form of hover effect)
- update name if the current audio changes
- properly split into subclasses

### Library
- create an expandable scrollbar for the library
  - show the current alphabet letter
- adjust appearance of library items
  - consider using a less "bright" white for less contrast
- improve smooth scrolling
  - maybe higher refresh rate
  - make it work properly on mouse and touchpad
- fix the bug where only one column is highlighted