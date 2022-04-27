#pragma once
#ifndef AUDIOCOMPRESSOR_CURVES_SINE_CURVE_H
#define AUDIOCOMPRESSOR_CURVES_SINE_CURVE_H

#include "curve.h"

typedef struct sine_curve sine_curve;

typedef sine_curve* sine_curve_handle;

sine_curve_handle sineCurve_ctor(void);

void sineCurve_dtor(sine_curve_handle curve);

#endif // AUDIOCOMPRESSOR_CURVES_SINE_CURVE_H