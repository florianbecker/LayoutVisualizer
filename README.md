# LayoutVisualizer
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fflorianbecker%2FLayoutVisualizer.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fflorianbecker%2FLayoutVisualizer?ref=badge_shield)

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

### Qt6
You can switch from Qt5 to Qt6 - default: Qt5
```cmake
# Enable Qt build - use Qt5 or Qt6
set(QtVERSION Qt6)
```


## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fflorianbecker%2FLayoutVisualizer.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fflorianbecker%2FLayoutVisualizer?ref=badge_large)