#pragma once

#include <stdio.h>

#include "2dMath.h"

void spline(Vec2 *points, int pointCount, Vec2 start, Vec2 control1, Vec2 control2, Vec2 end);
