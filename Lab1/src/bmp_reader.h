/*

*/

#ifndef BMP_READER_H
#define BMP_READER_H

#include <cstdint> // For precise bit control

#pragma pack(push, 1) // Disable compiler alignment of structures

// Data taken from Wikipedia ( 32-bit information fields BMP file)

// Structure for a BMP file header
struct BMP_Header {
    uint8_t ID[2]; // File identifier ('BM')
    uint32_t file_size; // BMP file size
    uint8_t unused[4]; // Reserved data
    uint32_t pixel_offset; // Offset to the start of pixel data
};

// Structure for DIB header
struct DIB_Header {
    uint32_t header_size; // DIB header size
    uint32_t width; // Image width in pixels
    uint32_t height; // Image height in pixels
    uint16_t color_planes; // Number of color planes
    uint16_t bits_per_pixel; // Number of bits per pixel
    uint32_t compression; // Compression type
    uint32_t data_size; // Size of pixel data
    uint32_t print_resolution_x; // Resolution along the X axis (in pixels per meter)
    uint32_t print_resolution_y; // Y-axis resolution (in pixels per meter)
    uint32_t colors_count; // Number of colors in the palette
    uint32_t important_colors; // Number of important colors
};

// Structure for the BMP file
struct BMP_File {
    BMP_Header bmp_header; // Header BMP
    DIB_Header dib_header; // Reader BIB
    uint8_t* file_data; // Pixel data
};

#pragma pack(pop) // Shutdown <pragma pack(push, 1)>

// Description function for load BMP file and freeing memory 
BMP_File* Load_BMP_File(const char* fname);
void Free_BMP_File(BMP_File* bmp_file);

#endif
