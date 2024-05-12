[![CMake](https://github.com/erzu12/cg_racer/actions/workflows/cmake.yml/badge.svg)](https://github.com/erzu12/cg_racer/actions/workflows/cmake.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=erzu12_cg_racer&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=erzu12_cg_racer)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=erzu12_cg_racer&metric=bugs)](https://sonarcloud.io/summary/new_code?id=erzu12_cg_racer)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=erzu12_cg_racer&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=erzu12_cg_racer)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=erzu12_cg_racer&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=erzu12_cg_racer)


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
