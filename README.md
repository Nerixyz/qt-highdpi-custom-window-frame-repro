# `qt-highdpi-custom-window-frame-repro`

| Bad | Better-But-Not-Great |
|---|---|
| <video src="https://user-images.githubusercontent.com/19953266/235311137-ab177f91-a19a-4c1b-b280-b8677c98a77f.mp4"> | <video src="https://user-images.githubusercontent.com/19953266/235311152-6c56842d-b9cf-4d2e-8a48-1fd9154dae89.mp4"> |


## Building

You can only build this app for Windows.
Qt `>=6.5` is expected to be installed in `$QT_INSTALL_PATH` (e.g. `C:\Qt\6.5.0\msvc2019_64`).

```powershell
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=$QT_INSTALL_PATH ..
cmake --build .
$QT_INSTALL_PATH\bin\windeployqt.exe --no-compiler-runtime --no-translations --no-opengl-sw --dir . xd.exe
```
