/*
 ButterFilter.cpp - Library for 2nd Order butterworth filter.
 Created by Montvydas Klumbys, 5 October, 2017.
 */

#include "Arduino.h"
#include "ButterFilter.h"

// constructor
ButterFilter::ButterFilter()
{
    this->v[0] = 0;
    this->v[1] = 0;
    this->v[2] = 0;
}

// setup out filter
void ButterFilter::begin(float cutoff, float fs)
{
    this->cutoff = cutoff;
    this->fs = fs;
    
    float f = tan(PI * cutoff / fs);
    float f2 = f * f;
    float sq2 = sqrt(2);
    
    float a0 = 1 + sq2 * f + f2;
    
    // Coefficients for 2nd order buttorworth filter
    this->a[1] = -2 * (f2 - 1) / a0;
    this->a[2] = -(1 - sq2 * f + f2) / a0;
    this->a[0] = f2 / a0;
}

// Used to get calculated coeeficients for testing
float* ButterFilter::getCoeffs()
{
    return a;
}

float ButterFilter::getCutoff()
{
    return this->cutoff;
}

float ButterFilter::getFs()
{
    return this->fs;
}

float ButterFilter::getLastFiltered(){
    return this->lastFiltered;
}

// Is used to apply a filter and get a new value
float ButterFilter::filter(float data)
{
    this->v[0] = this->v[1];
    this->v[1] = this->v[2];
    this->v[2] = this->a[0] * data + this->a[2] * this->v[0] + this->a[1] * this->v[1];
    
    this->lastFiltered = (this->v[0] + this->v[2])+ 2 * this->v[1];
    return this->lastFiltered;
}
