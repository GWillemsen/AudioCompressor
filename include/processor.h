#pragma once
#ifndef AUDIOCOMPRESSOR_PROCESSOR_H
#define AUDIOCOMPRESSOR_PROCESSOR_H

#include "curve.h"
#include <stddef.h>
#include <stdint.h>

typedef enum 
{
    CURVE_INDEX_0,
    CURVE_INDEX_1,
    CURVE_INDEX_2,
    CURVE_INDEX_3
} CurveIndex;

typedef enum
{
    PROCESSOR_MODE_ENCODE,
    PROCESSOR_MODE_DECODE,
} ProcessorMode;

typedef struct processor processor;
typedef processor* processor_handle;

typedef void (*processor_flushData_t)(processor_handle processor, uint8_t *data, size_t size, void *userdata);

processor_handle processor_ctor(ProcessorMode mode, processor_flushData_t sink, void *sinkUserdata);

void processor_dtor(processor_handle processor);

void processor_setCurve(processor_handle processor, CurveIndex index, curve *curve);

void processor_feedData(processor_handle processor, uint16_t *data, size_t size);

#endif // AUDIOCOMPRESSOR_PROCESSOR_H