#pragma once
#ifndef AUDIO_COMPRESSOR_CURVE_H
#define AUDIO_COMPRESSOR_CURVE_H

#include <stdint.h>

struct curve;

typedef void (*curve_SetScale_t)(struct curve* curve, uint32_t xMax, uint32_t yMax);
typedef uint32_t (*curve_GetValue_t)(struct curve* curve, uint32_t y);

typedef struct curve
{
    curve_GetValue_t getValue;
    curve_SetScale_t setScale;
} curve;

void curve_SetScale(curve* curve, uint32_t xMax, uint32_t yMax);

uint32_t curve_GetValue(curve* curve, uint32_t y);


#endif // AUDIO_COMPRESSOR_CURVE_H
