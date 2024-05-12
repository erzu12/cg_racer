# CG Racer

CG Racer is a project created for the module Computer Graphics at HSLU.
It allows you to create a simple racecourse with Bezier curves and race on it.

In the module SWAT, it is being refactored.

## Build

Make sure you have `gcc`, `glfw`, and `OpenGL` installed.
Then you can run:

Configure
```
cmake -DTARGET_GROUP=release -B build
```

Build
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

Build
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

## Overview

This is an overview of all the components and how they connect:

![overview](Docs/Components.svg)
