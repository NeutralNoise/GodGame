# TODO

If something was checked off but its not now just means more work needs to be done.
This will be added to as the project continues.
## Engine
- [ ] Rendering
  - [ ] Sprite Sheets.
  - [ ] Sprite rotation.
  - [ ] OpenGL render.
    - [ ] SDL2 OpenGL context
  - [ ] Custom DLL loading.
- [ ] Improve font rendering.
  - [ ] Not sure what I need for this just yet.
- [ ] Add frame rate limiting.
- [ ] Physics Engine.
  - [ ] Basic physics engine Separating Axis Theorem collision check.
    - [ ] This will serve as a wrapper for adding better physics engines later.
  - [ ] Box2D.
  - [ ] Make all movement not based on frame rate but on frame delta time.
    - [ ] This should be able to be turned off.
- [ ] Finished rendering engine.
  - [ ] The current one doesn't use the RenderLayer fully.
    - [ ] Each tile layer can only have one layer at the moment. Each layer should be able to have more then one layer.
    - [ ] Check if layer update is needed.
  - [ ] Add more statistics to InfoEngine about the rendering engine.
    - [ ] Frame count.
    - [ ] Frame time.
- [ ] Add debug information access with key press.
  - [ ] There should be configuration file that lets to pick what information is displayed.
  - [ ] The file should be reloadable.
- [x] Error message system.
- [ ] UI framework.
- [ ] Multi-Threading.
- [ ] Timers.
  - [x] Layer render time.
  - [x] Avg layer render time.
  - [ ] Layer Update time.
- [ ] Operating sytem (Windows is a given here.).
  - [ ] System information.
    - [ ] Windows.
    - [ ] Linux
  - [ ] Linux.
    - [ ] Make file.
    - [ ] Shared object (SO) loading.

## Experiment
- [ ] Set up engine to use a callback when running game logic.
  - [ ] The user can do what ever they whatever they want here.

## Game
* ???
* Something
* Even more something
* yeah I'm not here yet :D.
