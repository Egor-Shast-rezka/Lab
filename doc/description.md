# BMP Image Processing - Detailed Description

This document provides a detailed description of the `BMP_File` class and associated functions for working with BMP images, including their methods and time complexities.

## Structures

### BMP_Header
* **Description**: Represents the BMP file header, containing essential information about the file itself.
* **Members**:
    * `uint8_t ID[2]`: File identifier (e.g., 'BM' for BMP files)[cite: 106].
    * `uint32_t file_size`: The total size of the BMP file in bytes[cite: 107].
    * `uint8_t unused[4]`: Reserved data, typically set to 0[cite: 107].
    * `uint32_t pixel_offset`: The offset from the beginning of the file to the start of the pixel data[cite: 107].
* **Time Complexity (Construction)**: $O(1)$ [cite: 108]

### DIB_Header
* **Description**: Represents the Device Independent Bitmap (DIB) header, providing detailed information about the image pixels.
* **Members**:
    * `uint32_t header_size`: The size of the DIB header itself[cite: 109].
    * `uint32_t width`: The width of the image in pixels[cite: 110].
    * `uint32_t height`: The height of the image in pixels[cite: 110].
    * `uint16_t color_planes`: The number of color planes, typically 1[cite: 111].
    * `uint16_t bits_per_pixel`: The number of bits used to represent each pixel (e.g., 24 for true color)[cite: 111].
    * `uint32_t compression`: The compression method used for the image data[cite: 112].
    * `uint32_t data_size`: The size of the raw pixel data[cite: 112].
    * `uint32_t print_resolution_x`: Horizontal resolution in pixels per meter[cite: 113].
    * `uint32_t print_resolution_y`: Vertical resolution in pixels per meter[cite: 114].
    * `uint32_t colors_count`: The number of colors in the color palette, or 0 for true color images[cite: 115].
    * `uint32_t important_colors`: The number of important colors, or 0 if all colors are important[cite: 116].
* **Time Complexity (Construction)**: $O(1)$ [cite: 117]

### RGB
* **Description**: Represents a single 24-bit RGB pixel, with 8 bits for each color channel.
* **Members**:
    * `uint8_t blue`: Blue channel component (8 bits)[cite: 118].
    * `uint8_t green`: Green channel component (8 bits)[cite: 119].
    * `uint8_t red`: Red channel component (8 bits)[cite: 120].
* **Time Complexity (Construction)**: $O(1)$ [cite: 121]

## Class: BMP_File

### Overview
The `BMP_File` class encapsulates the data and operations related to a BMP image file. It holds the BMP header, DIB header, and the pixel data.

### Members
* `BMP_Header bmp_header`: The BMP file header[cite: 122].
* `DIB_Header dib_header`: The DIB header[cite: 122].
* `RGB* file_data`: A pointer to an array of `RGB` structures representing the pixel data[cite: 123].

### Public Methods

#### Constructor and Destructor
* `BMP_File()`
    * **Description**: Default constructor. Initializes `file_data` to `nullptr`[cite: 123].
    * **Time Complexity**: $O(1)$
* `~BMP_File()`
    * **Description**: Destructor. Deallocates the dynamically allocated `file_data` array[cite: 124].
    * **Time Complexity**: $O(1)$ (for deallocation, assuming `delete[]` is $O(1)$ for raw array, but effectively $O(N)$ for the underlying memory system depending on size).

#### File Operations
* `virtual bool Load_BMP_File(const char* file_name)`
    * **Description**: Loads a BMP image from the specified file. It reads the BMP and DIB headers, calculates row padding, and reads pixel data line by line, handling padding bytes[cite: 73, 75, 76, 77, 78, 79, 80, 81]. If the file cannot be opened, it prints an error and returns `false`[cite: 74, 75].
    * **Time Complexity**: $O(Width \times Height)$, as it iterates through each row and reads pixel data.
* `virtual void Save_BMP_File(const char* output_filename)`
    * **Description**: Saves the current BMP image data to the specified output file[cite: 82]. It writes the BMP and DIB headers, then iterates through pixel data, writing each row and appending necessary padding bytes[cite: 85, 86, 87, 88]. If the file cannot be opened for writing, it prints an error[cite: 83, 84].
    * **Time Complexity**: $O(Width \times Height)$, as it iterates through each pixel row for writing.

#### Image Transformations
* `std::unique_ptr<BMP_File> flip_BMP_90_contra_clockwise(int thread_count=4)`
    * **Description**: Rotates the BMP image 90 degrees counter-clockwise[cite: 90]. It creates a new `BMP_File` object, swaps its width and height dimensions, and then copies pixel data with the new orientation using multithreading for efficiency[cite: 91, 92, 93, 94, 95, 96].
    * **Time Complexity**: $O(Width \times Height / thread\_count)$ due to parallel processing, effectively $O(Width \times Height)$ in worst-case single thread, but faster with multiple threads for image processing.
* `std::unique_ptr<BMP_File> flip_BMP_90_clockwise(int thread_count=4)`
    * **Description**: Rotates the BMP image 90 degrees clockwise[cite: 98]. Similar to the counter-clockwise flip, it creates a new `BMP_File`, swaps dimensions, and copies pixel data with the new orientation using multithreading[cite: 99, 100, 101, 102, 103, 104].
    * **Time Complexity**: $O(Width \times Height / thread\_count)$, effectively $O(Width \times Height)$ in worst-case single thread, but faster with multiple threads for image processing.

## Global Functions

### `void GenereteGausKernel(int size, double sigma, double** gaussianKernel)`
* **Description**: Generates a Gaussian kernel of a specified `size` and `sigma` for image blurring[cite: 127]. It calculates the kernel values and then normalizes them so their sum is approximately 1, which helps in maintaining image brightness after filtering[cite: 128, 129].
* **Time Complexity**: $O(size^2)$, as it involves nested loops iterating up to `size` times for both dimensions of the kernel.

### `void ApplyGaussianFilter(BMP_File* bmp_file, int size, double sigma, int thread_count)`
* **Description**: Applies a Gaussian blur filter to the input `bmp_file` using the generated `gaussianKernel`[cite: 130, 131, 132]. This function utilizes multithreading to parallelize the filtering process across different rows of the image[cite: 139, 140, 141]. For each pixel, it calculates the new RGB values by convolving the pixel and its neighbors with the Gaussian kernel[cite: 134, 135, 136, 137, 138]. It then updates the `bmp_file`'s pixel data and deallocates temporary memory[cite: 143, 144].
* **Time Complexity**: $O((Width \times Height) / thread\_count \times kernel\_size^2)$ due to parallel processing and kernel convolution. In worst-case single thread, it's $O(Width \times Height \times kernel\_size^2)$. The outer rows (y=0 and y=height-1) are skipped[cite: 133].
