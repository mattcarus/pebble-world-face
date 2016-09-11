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
    { 4, -40 },
    { 0, -50},
    {-4, -40 }
  }
};