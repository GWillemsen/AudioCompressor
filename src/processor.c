#include <stdlib.h>
#include "Processor.h"

typedef struct processor
{
    processor_flushData_t flushData;
    void* userdata;
    ProcessorMode mode;
} processor;

processor_handle processor_ctor(ProcessorMode mode, processor_flushData_t sink, void* sinkUserdata)
{
    processor_handle handle = (processor_handle)calloc(sizeof(processor), 0);
    handle->flushData = sink;
    handle->userdata = sinkUserdata;
    handle->mode = mode;
    return handle;
}

void processor_dtor(processor_handle processor)
{
    free(processor);
}

void processor_setCurve(processor_handle processor, CurveIndex index, curve* curve)
{

}

void processor_feedData(processor_handle processor, uint16_t* data, size_t size)
{
    processor->flushData(processor, (uint8_t*)data, size * 2, processor->userdata);
}
