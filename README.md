# LayoutVisualizer
Layout Visualizer for Qt and Tools for Ui debugging
## SimpleDemo
<img src="workdata/simple.png" alt="macOS light theme" width="444" height="504"/><img src="workdata/simple_dark.png" alt="macOS dark theme" width="444" height="504"/>

## RasterWindow
Draw directly on window with QBackingStore.

## User-defined build variables
Inside cmake/env.cmake you will find some user-defined build variables for particular purposes.

### Debugging
You can log the verbose build output.
```cmake
# Debugging of build steps
set(CMAKE_VERBOSE_MAKEFILE ON)
```
