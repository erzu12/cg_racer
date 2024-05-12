# CG Racer

CG Racer is a project created for the module Computer Graphics at HSLU.
It allows you to make a simple racecource with bezzier curves and the race on it.

## Build

Make sure you have `gcc`, `glfw` and `opengl` installed.
Then you can run:


Configure
```
cmake -DTARGET_GROUP=release -B build
```

Buiild
```
cmake --build build
```

Run
```
./build/src/spaceracer
```

## Test

Configure
```
cmake -DTARGET_GROUP=test -B build
```

Buiild
```
cmake --build build
```

Run
```
cd build/test
```
```
ctest --output-on-failure
```
