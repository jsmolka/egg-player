# Things to do

## Rework
- proper query binding in database queries
- prevent filesystem from crashing when adding lots of files
- move filesystem classes into namespace
- remove qobject macro from objects without signals / slots
- before release: check / improve all classes

## User Interface
### Bar
- use different sliders for volume and duration and volume
  - make the volume slider pop out instead of hiding other icons
  - improve the duration slider style (include some form of hover effect)
- update name if the current audio changes
- properly split into subclasses
- fade to cover when changing

### Library
- create an expandable scrollbar for the library
- adjust appearance of library items
  - consider using a less "bright" white for less contrast
  - consider slightly smaller font size
- improve smooth scrolling
  - maybe higher refresh rate