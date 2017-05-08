# Age-of-Space

Space RTS project as a way to get started in C++ and object-oriented programming. Development started as a student project at the tech university of Madrid.

## Current tasks (rework)
- [x] Add task list to readme
- [x] Remove last added features
- [x] Remove every game objec
- [x] Redo ships
- [ ] Redo movement system
- [ ] Redo explosions (implement particle system)
- [ ] Redo projectiles
- [ ] Re-implement lists and basic interactions

## Future tasks (dev)
- [ ] Implement passive AI for ships
- [ ] Complete task list

## Version History

#### P 0.1:
- Basic class structure
- Single ship
- Mouse interaction: left click to select, right click to rotate

##### P 0.1.1:
- 100 ships for testing

#### P 0.2:
- Added linear movement for ships
- Black background, neon ship texture

#### P 0.3:
- Improved rendering
- Added multiple selection
- Resizeable textures
- New selection marker
- Global functions outside main file
- Screen divided into viewports

##### P 0.3.1:
- Added timers
- Added FPS cap and counter (console)
- 900 ship test (succesful)

##### P 0.3.2
- On screen text
- Removed viewports
- Main basic menu

##### P 0.3.3
- Interaction between asteroid and menu

#### P 0.4
- Screen divided into viewports (again)
- Viewport size linked to window size

#### P 0.5
- Added start screen
- Improved object rendering

#### P 0.6
- Added text input
- Players can input their name in the start screen

#### P 0.7
- Added resources and icons to top bar
- Bug fixes

#### P 0.8
- Implemented relative mouse mode and in-game cursor
- Resizeable window
- Added mouse scrolling
- Basic map layout
- Parallax implemented for background
- Slight code improvements
- Bug fixes
- Translated readme file

##### P 0.8.1
- Fixed mouse class so it makes a bit more sense
- Ships now can be selected and moved correctly
- Added some bugs

[Large gap due to work overload]

#### P 0.9
- A lot of code rewriting
- Bug fixing
- Ships now shoot and explode
- Enemy ships apear every few secconds
- Getting ready for realese
- New exciting and elusive bugs

#### P 0.10
- Bug fixes 'n suf
- Added a flippin' awesome minimap

#### P 0.11
- Ships can now actually move by themselves
- Enemy ships shoot at each other, or at least they try
- Added pause screen
- UI changes
- Deleted README file (woops!)

#### P 0.12
- Ships do slightly better at behaving like ships
- Ennemy ships will attack main building

[Development halted before sumer 2016]

##### P 0.12.1
- Variable names changed to fit new naming coventions
- Added funcitonalities to Vector2 class. It was so bare-bones I find it surprising how we got so many things done
- Added comments so I can understand what we did a year ago

#### P 0.13
- Disabled game phases, enemys, attacks, lists of entities... and many others for dev
- Fixed some of the bugs with mouse selection rectangle. There is still work to be done
- Improved and tweaked many little things
- Disabled rendering filter for textures so they would look pixelated instead of blurry
- Started re-implementing GameObjects and MovingObjects

##### P 0.13.1
- Re-implemented ship class
- Implemented smooth movement and hard stop
- Added optional vector rendering for debugging purposes (also it looks cool)
- Added new bug where last box selection appears when right clicking
- Added some fancy vector things for advanced math stuff
