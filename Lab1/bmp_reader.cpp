/*
    Egor Shastin st129457@student.spbu.ru
    This code contain functions for read, write BMP file and Free memory function.
*/

#include "bmp_reader.h"
#include <iostream>
#include <fstream>
#include <memory>

// Function for loading BMP file
std::unique_ptr<BMP_File> Load_BMP_File(const char* file_name)
{
    // Open file in reading mode
    std::ifstream file(file_name, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file: " << file_name << "\n";
        return nullptr;
    }
    
    // Smart pointer for bmp_file
    std::unique_ptr<BMP_File> bmp_file = std::make_unique<BMP_File>();

    // Read BMP header and DIB header
    file.read(reinterpret_cast<char*>(&bmp_file->bmp_header), sizeof(BMP_Header));
    file.read(reinterpret_cast<char*>(&bmp_file->dib_header), sizeof(DIB_Header));

    // Calculate pixel count and allocate memory for pixel data
    uint32_t pixel_count = bmp_file->dib_header.width * bmp_file->dib_header.height;
    bmp_file->file_data = new RGB[pixel_count];
    
    // Move file pointer to the beginning of pixel data
    file.seekg(bmp_file->dib_header.header_size + 14, std::ios::beg);

    // Row size (with padding) is aligned to 4 bytes
    int row_size = ((bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel + 31) / 32) * 4;
    
    // Reading pixel data using reinterpret_cast
    for (int y = bmp_file->dib_header.height - 1; y >= 0; --y)
    {
        // Read file line by line
        file.read(reinterpret_cast<char*>(&bmp_file->file_data[y * bmp_file->dib_header.width]), bmp_file->dib_header.width * sizeof(RGB));
        
        file.seekg(row_size - bmp_file->dib_header.width * sizeof(RGB), std::ios::cur);
    }

    file.close(); // Close file
    return bmp_file;
}

// Function to save BMP file
void Save_BMP_File(const BMP_File* bmp_file, const char* output_filename)
{
    // Open file for writing
    std::ofstream file(output_filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file for writing: " << output_filename << "\n";
        return;
    }

    // Write BMP header and DIB header
    file.write(reinterpret_cast<const char*>(&bmp_file->bmp_header), sizeof(BMP_Header));
    file.write(reinterpret_cast<const char*>(&bmp_file->dib_header), sizeof(DIB_Header));
    
    file.seekp(bmp_file->dib_header.header_size + 14, std::ios::beg);

    // Calculate padding
    uint32_t row_size = ((bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel + 31) / 32) * 4;
    uint32_t padding = row_size - (bmp_file->dib_header.width * bmp_file->dib_header.bits_per_pixel / 8);

    // Write pixels in file
    for (int y = bmp_file->dib_header.height - 1; y >= 0; --y)
    {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x)
        {
            uint32_t pixel_index = y * bmp_file->dib_header.width + x;
            file.put(bmp_file->file_data[pixel_index].blue);
            file.put(bmp_file->file_data[pixel_index].green);
            file.put(bmp_file->file_data[pixel_index].red);
        }

        // Addition padding
        for (uint32_t p = 0; p < padding; ++p)
        {
            file.put(0);
        }
    }

    file.close(); // File close
    std::cout << "Image saved successfully to " << output_filename << "\n";
}


// Function for flip BMP file contra clockwise
std::unique_ptr<BMP_File> flip_BMP_90_contra_clockwise(BMP_File* bmp_file)
{
    std::unique_ptr<BMP_File> new_bmp_file = std::make_unique<BMP_File>();

    // Copy headers into the new BMP file
    new_bmp_file->bmp_header = bmp_file->bmp_header;
    new_bmp_file->dib_header = bmp_file->dib_header;

    // Swap width and height
    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    // Calculate new image size
    uint32_t new_pixel_count = new_bmp_file->dib_header.width * new_bmp_file->dib_header.height;
    new_bmp_file->file_data = new RGB[new_pixel_count];

    for (uint32_t y = 0; y < bmp_file->dib_header.height; ++y)
    {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x)
        {
            // Calculate the old pixel index
            uint32_t old_index = y * bmp_file->dib_header.width + x;

            // Calculate the new position for the pixel
            uint32_t new_index = (bmp_file->dib_header.width - 1 - x) * new_bmp_file->dib_header.width + y;

            // Copy the pixel to the new position
            new_bmp_file->file_data[new_index] = bmp_file->file_data[old_index];
        }
    }
    
    return new_bmp_file;
}

// Function for flip BMP file clockwise
std::unique_ptr<BMP_File> flip_BMP_90_clockwise(BMP_File* bmp_file)
{
    std::unique_ptr<BMP_File> new_bmp_file = std::make_unique<BMP_File>();

    // Copy headers into the new BMP file
    new_bmp_file->bmp_header = bmp_file->bmp_header;
    new_bmp_file->dib_header = bmp_file->dib_header;

    // Swap width and height
    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    // Calculate new image size
    uint32_t new_pixel_count = new_bmp_file->dib_header.width * new_bmp_file->dib_header.height;
    new_bmp_file->file_data = new RGB[new_pixel_count];

    for (uint32_t y = 0; y < bmp_file->dib_header.height; ++y)
    {
        for (uint32_t x = 0; x < bmp_file->dib_header.width; ++x)
        {
            // Calculate the old pixel index
            uint32_t old_index = y * bmp_file->dib_header.width + x;

            // Calculate the new position for the pixel
            uint32_t new_index = x * new_bmp_file->dib_header.width + (bmp_file->dib_header.height - 1 - y);

            // Copy the pixel to the new position
            new_bmp_file->file_data[new_index] = bmp_file->file_data[old_index];
        }
    }

    return new_bmp_file;
}

