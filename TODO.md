# TODO

1. If something was checked off but its not now just means more work needs to be done.
2. This will be added to as the project continues.
3. ?? means either I'm thinking about this or nothing has came up that requires action.
## Engine

### Rendering.

- [ ] Rendering
  - [ ] Inherited renderer class.
  - [ ] Sprite Sheets.
  - [ ] Sprite rotation.
  - [ ] Sprite batching.
  - [ ] RenderLayers
    - [ ] Each layer should be able to have more then one layer.
    - [ ] Check if layer update is needed.
  - [ ] SDL2
    - [ ] Render to texture/surface (for post processing.)
    - [ ] Lighting.
    - [ ] Post processing. (Done on the CPU)
      - [ ] Gaussian Blur.
      - [ ] Bloom.
      - [ ] Motion blur.
  - [ ] OpenGL render.
    - [ ] SDL2 OpenGL context
    - [ ] Shaders.
      - [ ] Shader loading.
      - [ ] Shader compiling.
      - [ ] Basic image display shader.
        - [ ] Rander to FBO for post processing.
      - [ ] Lighting.
      - [ ] Post processing.
        - [ ] Gaussian Blur.
        - [ ] Bloom.
        - [ ] Motion blur.
      - [ ] Uniforms.
      - [ ] Custom shaders.
  - [ ] VSYNC.

### File system.

- [ ] File system.
  - [ ] Open files.
  - [ ] Save files.
  - [ ] Virtual File System (VFS).
  - [ ] Json files.
    - [ ] Jsoncpp wrapper.

### Fonts.

- [ ] Improve font rendering.
  - [ ] Font manager.
    - [ ] Load fonts.
    - [ ] Generate text texute from the fonts.
    - [ ] Geterate sprite glyth from font. (Mainly for OpenGL).
    - [ ] Store FontText.
  - [ ] FontText
    - [ ] Store last used text.
    - [ ] Store last generated text texture.

### Physics.

- [ ] Physics Engine.
  - [ ] Inherited physics class.
  - [ ] Physics body.
    - [ ] Rotation.
  - [ ] Basic physics engine.
    - [ ] Menifold generation.
    - [ ] Separating Axis Theorem collision check.
      - [ ] Box.
      - [ ] Circle.
      - [ ] Edge.
      - [ ] Chain.
      - [ ] Polygon (custom shape.)
    - [ ] Friction.
    - [ ] Velocity.
    - [ ] Gravity.
    - [ ] Mass.
    - [ ] World (Where all the collisions happen.)
      - [ ] Add shape.
      - [ ] Remove shape.
      - [ ] Update bodys.
        - [ ] Only check whats near the body.
    - [ ] Wish list (Things that might get added.)
      - [ ] Joints.
      - [ ] Springs.
      - [ ] Ray cast.
  - [ ] Box2D.
  - [ ] Make all movement not based on frame rate but on frame delta time.
    - [ ] Interpolation.
- [ ] Add debug information access with key press.

### Config.

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

### Statistics.

- [ ] Statistics
  - [ ] Timers.
    - [x] Layer render time.
    - [x] Avg layer render time.
    - [ ] Frame time.
    - [ ] Layer Update time.
    - [ ] Physis update time
      - [ ] Total time.
      - [ ] Avg object update time.
    - [ ] ??
  - [ ] Counters.
    - [ ] Drawn sprites.
    - [ ] Draw calls.
    - [ ] Frame rate.
    - [ ] Avg drawn sprites.
    - [ ] Avg draw calls.
    - [ ] Loaded textures.
    - [ ] Physis objects.
  - [ ] System.
    - [ ] Memory useage.
    - [ ] CPU useage.
    - [ ] GPU useage.

### Operating system.

- [ ] Operating sytem (Windows is a given here.).
  - [ ] System information.
    - [ ] Windows.
    - [ ] Linux.
    - [ ] Hardware.
      - [ ] CPUID
      - [ ] GPUID
      - [ ] Total memory avaiable.
  - [ ] Linux.
    - [ ] Make file (for compiling)
    - [ ] Shared object (SO) loading.

### Optimisation.

- [ ] Optimisation.
  - These will be on going and maybe check and unchecked whenever.
  - [ ] Rendering.
    - [ ] ~~Only check the layer where the camera is looking.~~ (This should be done by the user and not the engine when creating the sprite batch)
    - [ ] ??

### Networking

- [ ] Networking.

### Audio.

- [ ] Audio.
  - [ ] OpenAL soft wrapper.
    - [ ] Load sound.
    - [ ] Play sound.
    - [ ] Pause sound.
- [ ] ??

### User interface.

- [ ] UI framework.
  - [ ] Options (These will need a wrapper to work with SDL2 rendering.)
    - [ ] [Nuklear](https://github.com/vurtun/nuklear)
    - [ ] [Imgui](https://github.com/ocornut/imgui)
  - [ ] Triggers.
  - [ ] Text box.
    - [ ] Scrolling
  - [ ] Load bar.
  - [ ] Buttons.
  - [ ] Image display.

### Misc

- [x] Error message system.


## Experiment
- [ ] Set up engine to use a callback when running game logic.
  - [ ] The user can do what ever they whatever they want here.
- [ ] Multi-Threading.

## Game
* ???
* Something
* Even more something
* yeah I'm not here yet :D.
