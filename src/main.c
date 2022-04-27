#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "curve.h"
#include "processor.h"
#include "string.h"

bool open_io_files(FILE** fin, FILE **fout, const char* finName, const char* foutName);
bool create_processor(processor_handle *processor, FILE* fout, const char* mode);
void processor_flushData(processor_handle processor, uint8_t *data, size_t size, void *userdata);

int main(int argc, const char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Arguments not correct. Only expect 3 arguments. 1 in and 1 out file. And a mode value. Argument count was: %i.\n", argc);
        return -1;
    }
    FILE *fin = NULL;
    FILE *fout = NULL;
    if (open_io_files(&fin, &fout, argv[2], argv[3]) == false)
    {
        return -1;
    }
    else
    {
        printf("Opening files successfull.\n");
    }

    processor_handle fileProcessor;
    if (create_processor(&fileProcessor, fout, argv[1]) == false)
    {
        fclose(fin);
        fclose(fout);
        return -1;
    }
    else
    {
        printf("Creating processor successfull.\n");
    }

    const size_t kBufferSize = 2048;
    uint16_t buffer[4096] = { 0 };
    size_t samplesRead = 0;
    do
    {
        samplesRead = fread(buffer, sizeof(uint16_t), kBufferSize, fin);
        printf("Reading buffer successfull.\n");
        if (samplesRead > 0)
        {
            processor_feedData(fileProcessor, buffer, samplesRead);
        }
    } while(samplesRead > 0);

    fclose(fin);
    fclose(fout);
    processor_dtor(fileProcessor);
    return 0;
}

bool open_io_files(FILE** fin, FILE **fout, const char* finName, const char* foutName)
{
    if (fin == NULL || fout == NULL)
    {
        return false;
    }

    *fin = fopen(finName, "r");
    if (fin == NULL)
    {
        fprintf(stderr, "Failed to open input file. Aborting.\n");
        return false;
    }
    *fout = fopen(foutName, "w");
    if (fout == NULL)
    {
        fprintf(stderr, "Failed to open output file. Aborting.\n");
        return false;
    }
    return true;
}

bool create_processor(processor_handle *processor, FILE* fout, const char* mode)
{
    const char *decodeName = "decode";
    const char *encodeName = "encode";
    if (strncmp(decodeName, mode, strlen(decodeName)) == 0)
    {
        *processor = processor_ctor(PROCESSOR_MODE_DECODE, processor_flushData, fout);
    }
    else if (strncmp(encodeName, mode, strlen(encodeName)) == 0)
    {
        *processor = processor_ctor(PROCESSOR_MODE_ENCODE, processor_flushData, fout);        
    }
    return *processor != NULL;
}

void processor_flushData(processor_handle processor, uint8_t *data, size_t size, void *userdata)
{
    FILE* fout = (FILE*)userdata;
    fwrite(data, sizeof(uint8_t), size, fout);
}
