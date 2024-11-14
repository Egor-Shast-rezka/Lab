/*
    Egor Shastin st129457@student.spbu.ru
    This code contain function for filter gaus.
*/

#include "bmp_reader.h"
#include <cmath>
// Я хочу, чтобы размер ядра можно было задавать
// Its define the kernel (3*3) for Gaussian filter
double gaussianKernel[3][3] = {
    { 1.0 / 16, 2.0 / 16, 1.0 / 16 },
    { 2.0 / 16, 4.0 / 16, 2.0 / 16 },
    { 1.0 / 16, 2.0 / 16, 1.0 / 16 }
};

// Function to apply Gaussian filter to an image
void ApplyGaussianFilter(BMP_File* bmp_file) {
    int width = bmp_file->dib_header.width;
    int height = bmp_file->dib_header.height;

    // Create buffer to store result
    RGB* file_data = new RGB[width * height];

    // Apply Gausian filter line by line
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double red = 0.0, green = 0.0, blue = 0.0;

            // Aply Gaussian kernel to a 3x3 window of pixels
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    RGB pixel = bmp_file->file_data[(y + ky) * width + (x + kx)];
                    red += pixel.red * gaussianKernel[ky + 1][kx + 1];
                    green += pixel.green * gaussianKernel[ky + 1][kx + 1];
                    blue += pixel.blue * gaussianKernel[ky + 1][kx + 1];
                }
            }

            // Write the reslt to the output buffer
            file_data[y * width + x] = RGB(
                static_cast<uint8_t>(std::min(std::max(red, 0.0), 255.0)),
                static_cast<uint8_t>(std::min(std::max(green, 0.0), 255.0)),
                static_cast<uint8_t>(std::min(std::max(blue, 0.0), 255.0))
            );
        }
    }

    // Copy the procesed data back original image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bmp_file->file_data[y * width + x] = file_data[y * width + x];
        }
    }

    // Free memory for the result
    delete[] file_data;
}


