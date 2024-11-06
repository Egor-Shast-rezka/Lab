/*

*/

#include "bmp_reader.h"
#include <iostream>
#include <fstream>

// Function for loading BMP file
BMP_File* Load_BMP_File(const char* fname) {
    // Open file in reading mode
    std::ifstream file(fname, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file: " << fname << "\n";
        return nullptr;
    }

    BMP_File* bmp_file = new BMP_File(); // Memory alocation for BMP_File

    file.read(reinterpret_cast<char*>(&bmp_file->bmp_header), sizeof(BMP_Header)); // Read header BMP
    
    // Check if file is BMP format
    if (bmp_file->bmp_header.ID[0] != 'B' || bmp_file->bmp_header.ID[1] != 'M') {
        std::cerr << "Invalid file format!" << "\n";
        delete bmp_file;
        return nullptr;
    }

    file.read(reinterpret_cast<char*>(&bmp_file->dib_header), sizeof(DIB_Header)); // Read header DIB

    // Reading pixel data
    
    bmp_file->file_data = new uint8_t[bmp_file->dib_header.data_size]; // Allocate memory for the number of DIB bytes
    
    file.seekg(bmp_file->bmp_header.pixel_offset, std::ios::beg); // The offset to pixels is specified in the BMP header.
    
    file.read((char*)bmp_file->file_data, bmp_file->dib_header.data_size); // Read pixel data into file_data array.

    file.close(); // Close file
    return bmp_file;
}

// Function to free memory
void Free_BMP_File(BMP_File* bmp_file) {
    if (bmp_file) {
        delete[] bmp_file->file_data; // Freeing memory for array pixels
        delete bmp_file; // Freeing memory for BMP_File
    }
}
