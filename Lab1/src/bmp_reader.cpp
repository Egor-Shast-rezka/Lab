/*

*/

#include "bmp_reader.h"
#include <iostream>
#include <fstream>

// Function for loading BMP file
BMP_File* Load_BMP_File(const char* file_name) {
    // Open file in reading mode
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file: " << file_name << "\n";
        return nullptr;
    } 
    BMP_File* bmp_file = new BMP_File(); // Allocate memory for BMP_File

    // Read BMP header and DIB header using reinterpret_cast
    file.read(reinterpret_cast<char*>(&bmp_file->bmp_header), sizeof(BMP_Header));
    file.read(reinterpret_cast<char*>(&bmp_file->dib_header), sizeof(DIB_Header));

    // Calculating pixel count and allocating memory for pixel data
    uint32_t pixel_count = bmp_file->dib_header.width * bmp_file->dib_header.height;
    bmp_file->file_data = new RGB[pixel_count];

    // Move file pointer to the beginning of pixel data
    file.seekg(bmp_file->dib_header.header_size + 14, std::ios::beg);

    // Row size (with padding) is aligned to 4 bytes
    int row_size = ((bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel + 31) / 32) * 4;

    // Reading pixel data using reinterpret_cast
    for (int y = bmp_file->dib_header.height - 1; y >= 0; --y) {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x) {
            // Read each pixel's RGB components using reinterpret_cast
            file.read(reinterpret_cast<char*>(&bmp_file->file_data[y * bmp_file->dib_header.width + x]), sizeof(RGB));
        }
        // Skip padding bytes if any (BMP rows are padded to 4-byte boundaries)
        file.seekg(row_size - bmp_file->dib_header.width * sizeof(RGB), std::ios::cur);
    }
    file.close(); // Close file
    return bmp_file;
}


// Function to free memory
void Free_BMP_File(BMP_File* bmp_file) {
    if (bmp_file) {
        delete[] bmp_file->file_data; // Freeing memory for array pixels
        delete bmp_file; // Freeing memory for BMP_File
    }
    std::cout << "Memory free." << "\n\n"; 
}

// Function for flip BMP file contra clockwise
BMP_File* flip_BMP_90_contra_clockwise(BMP_File* bmp_file) {
    BMP_File* new_bmp_file = new BMP_File();
    
    // Copy header in new BMP file
    new_bmp_file->bmp_header = bmp_file->bmp_header;
    new_bmp_file->dib_header = bmp_file->dib_header;
    
    // Swap width and height
    new_bmp_file->dib_header.width = bmp_file->dib_header.height;
    new_bmp_file->dib_header.height = bmp_file->dib_header.width;

    // Colculate size new imagine
    uint32_t new_pixel_count = new_bmp_file->dib_header.width * new_bmp_file->dib_header.height;
    new_bmp_file->file_data = new RGB[new_pixel_count];

    for (uint32_t y = 0; y < bmp_file->dib_header.height; ++y) {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x) {
            // Search old index pixel
            uint32_t old_index = y * bmp_file->dib_header.width + x;

            // Colculate new position for pixel
            uint32_t new_index = (bmp_file->dib_header.width - 1 - x) * new_bmp_file->dib_header.width + y;

            // Copy pixel on new position
            new_bmp_file->file_data[new_index] = bmp_file->file_data[old_index];
        }
    }
    return new_bmp_file;
}

// Function for flip BMP file clockwise
BMP_File* flip_BMP_90_clockwise(BMP_File* bmp_file){
    return flip_BMP_90_contra_clockwise(flip_BMP_90_contra_clockwise(flip_BMP_90_contra_clockwise(bmp_file)));
}

// Function for save new file
void Save_BMP_File(const BMP_File* bmp_file, const char* output_filename) {
    // Open file
    std::ofstream file(output_filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file for writing: " << output_filename << "\n";
        return;
    }
    
    
    // Copy header BMP and DIB in new file
    file.write(reinterpret_cast<const char*>(&bmp_file->bmp_header), sizeof(BMP_Header));
    file.write(reinterpret_cast<const char*>(&bmp_file->dib_header), sizeof(DIB_Header));
    
    file.seekp(bmp_file->dib_header.header_size + 14, std::ios::beg);

    // Colculate padding
    uint32_t row_size = ((bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel + 31) / 32) * 4;
    uint32_t padding = row_size - (bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel / 8);

    // Write pixels in file
    for (int y = bmp_file->dib_header.height - 1; y >= 0; --y) {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x) {
        
            uint32_t pixel_index = y * bmp_file->dib_header.width + x; // Position pixel
            
            file.put(bmp_file->file_data[pixel_index].blue);
            file.put(bmp_file->file_data[pixel_index].green);
            file.put(bmp_file->file_data[pixel_index].red);
        }

        // Addition padding
        for (uint32_t p = 0; p < padding; ++p) {
            file.put(0);
        }
    }
    
    // File close
    file.close();
    std::cout << "Image saved successfully to " << output_filename << "\n";
}


