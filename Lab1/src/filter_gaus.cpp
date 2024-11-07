/*

*/

#include "filter_gaus.h"
#include <cmath>

// Function to create a 1D Gaussian kernel
double* CreateGaussianKernel(double sigma, int kernel_radius) {
    int size = 2 * kernel_radius + 1;  // Kernel size is 2 * radius + 1
    double* kernel = new double[size]; // Allocate memory for kernel
    double sum = 0.0; // To accumulate sum for normalization

    // Fill the kernel with Gaussian values
    for (int i = -kernel_radius; i <= kernel_radius; ++i) {
        // Gaussian formula for 1D
        kernel[i + kernel_radius] = std::exp(-(i * i) / (2 * sigma * sigma)) / (std::sqrt(2 * M_PI) * sigma);
        sum += kernel[i + kernel_radius]; // Accumulate sum
    }

    // Normalize the kernel (so that the sum of all elements equals 1)
    for (int i = 0; i < size; ++i) {
        kernel[i] /= sum;
    }

    return kernel; // Return the Gaussian kernel
}

// Function to apply a 1D convolution to the image
void Apply_Convolution(const BMP_File* bmp_file, BMP_File* result, const double* kernel, int kernel_radius, bool horizontal) {
    int width = bmp_file->dib_header.width;
    int height = bmp_file->dib_header.height;

    // Loop through each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r_sum = 0.0, g_sum = 0.0, b_sum = 0.0; // To accumulate color values

            // Apply the convolution with the Gaussian kernel
            for (int k = -kernel_radius; k <= kernel_radius; ++k) {
                int sample_x = x, sample_y = y; // Coordinates of the sample pixel

                // If horizontal, move x, otherwise move y (vertical)
                if (horizontal) {
                    sample_x = std::min(std::max(x + k, 0), width - 1); // Handle image edges
                } else {
                    sample_y = std::min(std::max(y + k, 0), height - 1); // Handle image edges
                }

                // Get the pixel from the original image
                int index = sample_y * width + sample_x;
                const RGB& pixel = bmp_file->file_data[index];

                // Multiply pixel color values by the kernel and add to the sum
                r_sum += pixel.red * kernel[k + kernel_radius];
                g_sum += pixel.green * kernel[k + kernel_radius];
                b_sum += pixel.blue * kernel[k + kernel_radius];
            }

            // Save the new color values to the result image
            int new_index = y * width + x;
            result->file_data[new_index].red = static_cast<uint8_t>(std::min(std::max(r_sum, 0.0), 255.0));
            result->file_data[new_index].green = static_cast<uint8_t>(std::min(std::max(g_sum, 0.0), 255.0));
            result->file_data[new_index].blue = static_cast<uint8_t>(std::min(std::max(b_sum, 0.0), 255.0));
        }
    }
}

// Main function to apply the Gaussian filter to the BMP image
BMP_File* ApplyGaussianFilter(const BMP_File* bmp_file, double sigma, int kernel_radius) {
    // Create result image
    BMP_File* result = new BMP_File();
    result->bmp_header = bmp_file->bmp_header;
    result->dib_header = bmp_file->dib_header;
    int pixel_count = bmp_file->dib_header.width * bmp_file->dib_header.height;
    result->file_data = new RGB[pixel_count];

    // Create the Gaussian kernel
    double* kernel = CreateGaussianKernel(sigma, kernel_radius);

    // Create temporary image for intermediate results (horizontal pass)
    BMP_File* temp_result = new BMP_File();
    temp_result->bmp_header = bmp_file->bmp_header;
    temp_result->dib_header = bmp_file->dib_header;
    temp_result->file_data = new RGB[pixel_count];

    // First pass: Apply convolution horizontally
    Apply_Convolution(bmp_file, temp_result, kernel, kernel_radius, true);

    // Second pass: Apply convolution vertically
    Apply_Convolution(temp_result, result, kernel, kernel_radius, false);

    // Clean up temporary image and kernel
    delete[] temp_result->file_data;
    delete temp_result;
    delete[] kernel;

    // Return the result image
    return result;
}
