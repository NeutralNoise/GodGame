# TODO

1. If something was checked off but its not now just means more work needs to be done.
2. This will be added to as the project continues.
3. ?? means either I'm thinking about this or nothing has came up that requires action.
## Engine
- [ ] Rendering
  - [ ] Inherited renderer class.
  - [ ] Sprite Sheets.
  - [ ] Sprite rotation.
  - [ ] Sprite batching.
  - [ ] OpenGL render.
    - [ ] SDL2 OpenGL context
    - [ ] Shader loading.
      - [ ] Basic image display shader.
      - [ ] Custom shaders.
      - [ ] Shader compiling.
        - [ ] Uniforms.
  - [ ] Custom DLL loading.
- [ ] File system.
  - [ ] Open files.
  - [ ] Save files.
  - [ ] Virtual File System (VFS).
  - [ ] Json files.
    - [ ] Jsoncpp wrapper.
- [ ] Improve font rendering.
  - [ ] Font manager.
    - [ ] Load fonts.
    - [ ] Generate text texute from the fonts.
    - [ ] Geterate sprite glyth from font. (Mainly for OpenGL).
    - [ ] Store FontText.
  - [ ] FontText
    - [ ] Store last used text.
    - [ ] Store last generated text texture.
- [ ] Frame rate limiting.
  - [ ] VSYNC.
  - [ ] Configurable option.
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
- [ ] Config File.
  - [ ] Loads JSON file.
  - [ ] Command line arguments override JSON file.
  - [ ] Options.
    - [ ] Frame rate.
    - [ ] Physics frame rate.
    - [ ] Profiling on or off.
    - [ ] Debug information.
      - [ ] Choose what to display.
    - [ ] Networking options?
    - [ ] Max memory useage.
      - [ ] All loaders will need to check this.
      - [ ] Default is use all memory.
  - [ ] Reloadable while running.
    - [ ] Auto detected changes.
    - [ ] With key press.
- [x] Error message system.
- [ ] UI framework.
- [ ] Statistics
  - [ ] Timers.
    - [x] Layer render time.
    - [x] Avg layer render time.
    - [ ] Layer Update time.
    - [ ] Physis update time
      - [ ] Total time.
      - [ ] Avg object update time.
    - [ ] ??
  - [ ] Counters.
    - [ ] Drawn sprites.
    - [ ] Draw calls.
    - [ ] Avg drawn sprites.
    - [ ] Avg draw calls.
    - [ ] Loaded textures.
    - [ ] Physis objects.
  - [ ] System.
    - [ ] Memory useage.
    - [ ] CPU useage.
    - [ ] GPU useage.
- [ ] Operating sytem (Windows is a given here.).
  - [ ] System information.
    - [ ] Windows.
    - [ ] Linux.
    - [ ] Hardware.
      - [ ] CPUID
      - [ ] GPUID
      - [ ] Total memory avaiable.
  - [ ] Linux.
    - [ ] Make file.
    - [ ] Shared object (SO) loading.
  - [ ] Optimisation.
    - These will be on going and maybe check and unchecked whenever.
    - [ ] Rendering.
      - [ ] ~~Only check the layer where the camera is looking.~~ (This should be done by the user and not the engine when creating the sprite batch)
      - [ ] ??
    - [ ] ??

## Experiment
- [ ] Set up engine to use a callback when running game logic.
  - [ ] The user can do what ever they whatever they want here.
- [ ] Multi-Threading.

## Game
* ???
* Something
* Even more something
* yeah I'm not here yet :D.
