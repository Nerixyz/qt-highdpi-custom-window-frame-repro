# `qt-highdpi-custom-window-frame-repro`

## Building

You can only build this app for Windows.
Qt `>=6.5` is expected to be installed in `$QT_INSTALL_PATH` (e.g. `C:\Qt\6.5.0\msvc2019_64`).

```powershell
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=$QT_INSTALL_PATH ..
cmake --build .
$QT_INSTALL_PATH\bin\windeployqt.exe --no-compiler-runtime --no-translations --no-opengl-sw --dir . xd.exe
```
