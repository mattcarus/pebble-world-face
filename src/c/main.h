#include <pebble.h>
#pragma once

#include "pebble.h"

static const GPathInfo MINUTE_HAND_POINTS = {
  5, (GPoint []) {
    { -2, 0 },
    { 2, 0 },
    { 3, -52 },
    { 0, -62 },
    {-3, -52 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  5, (GPoint []){
    {-2, 0 },
    { 2, 0 },
    { 4, -32 },
    { 0, -40},
    {-4, -32 }
  }
};

// Plane image
static const GPathInfo SECOND_HAND_POINTS = {
  16, (GPoint []){
    { -14, -36 },
    { -10, -31 },
    { 0, -32 },
    { -5, -42 },
    { 0, -42 },
    { 7, -32 },
    { 15, -32 },
    { 17, -30 },
    { 15, -28 },
    { 7, -28 },
    { 0, -18 },
    { -5, -18 },
    { 0, -28 },
    { -10, -29 },
    { -14, -24 },
    { -12, -30}
  }
};