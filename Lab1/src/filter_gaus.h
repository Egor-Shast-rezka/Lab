/*

*/

#ifndef FILTER_GAUS_H
#define FILTER_GAUS_H

#include "bmp_reader.h" 

BMP_File* ApplyGaussianFilter(const BMP_File* bmp_file, double sigma, int kernel_radius);

#endif
