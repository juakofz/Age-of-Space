# Age-of-Space

Space RTS project as a way to get started in C++ and object-oriented programming. Development started as a student project at the tech university of Madrid.
Initial development by @juakofz and @cheriperi.

## Current tasks (rework)
- [x] Implement health correctly
- [ ] Make ships shoot again
- [ ] Make ships repel each other when too close

## Less inmediate tasks
- [x] Re-implement lists and basic interactions
- [ ] Make movement feel more... organic?
- [ ] Add UI features such as buttons, text, etc.
- [ ] Improve debug mode
- [ ] Clean up img folder and implement proper ressource 
loading
- [ ] Add support for animations
- [ ] Add ship destruction animation


## Future tasks (dev)
- [ ] Implement passive AI for ships
- [ ] Complete task list

## Known bugs
- Timers are not quite working
- Viewports sometimes fail to initialise and renders only background color until alt-tabbing out and in again (probably fixed)
- Mouse events get locked on last position when changing screen area

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

##### P 0.13.2
- New movement system that looks pretttty niiice
- Added more debug rendering
- Red screen bug keeps getting worse

##### P 0.13.3
- Improved keyboard imput management
- Press F12 to toggle debug mode
- Added ObjectManager class for object management

##### P 0.13.4
- Added ObjectManager, which will be both an object factory and game object manager
- Added Projectile vector and dynamic projectile management
- Added Explosion vector (WIP)
- Debug key changed to "d"

##### P 0.13.5
- Added dynamic explosion management
- Added different kinds of projectiles
- Added dynamic ship management
- Ships now die when hit by any projectile (including explosions). Health is being implemented
- Added progress bars (for health bars ans such)
- Added a better random number generating system

##### P 0.13.6
- Added good health and damage management
- Health bars added to debug mode
- Bug fixing
- Laid groundwork for weapon systems (lists n' stuff)

##### P 0.13.7
- Added weapons to ships, although they don't shoot yet
- Ships repel each other so they don't fuse into one. This needs quite a lot of optimization still
- Added some enums for types and sizes
- Objectmanager made into a singleton (this may not be necessary)
- Added a request list for object creation. Not yet fully implementeded