#include "curve.h"
#include "curves/sine_curve.h"

typedef struct sine_curve
{
    curve base;
    int xScale;
    int yScale;
} sine_curve;

sine_curve_handle sineCurve_ctor(void)
{
    return 0;
}

void sineCurve_dtor(sine_curve_handle curve)
{

}
