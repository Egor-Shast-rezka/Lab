/*
    Egor Shastin st129457@student.spbu.ru
    This code is a general in all project, it run program and print commits.
*/

#include "bmp_reader.h"
#include "filter_gaus.h"
#include <iostream>

// The program reads an image called example.bmp
int main(int argc, char* argv[])
{

    // Check heving two arguments
    if (argc < 2)
    {
        std::cout << "Using: " << argv[0] << " <path to BMP file>" << "\n"; // If the file path is not specified
        return 0;
    }

    BMP_File* bmp_file = Load_BMP_File(argv[1]); // Create array for BMP imagine

    if (!bmp_file)
    {
        std::cerr << "Failed to load BMP file." << "\n";
        return -1;
    }
    else
    {
        std::cout << "BMP File read succesful." << "\n";
    }

    std::cout << "BMP file size:" << bmp_file->bmp_header.file_size << " byte" << "\n";
    std::cout << "-> First task completed: file size printed." << "\n\n";

    // Flip BMP contra clockwise
    BMP_File* new_bmp_file_1 = flip_BMP_90_contra_clockwise(bmp_file);
    Save_BMP_File(new_bmp_file_1, "BMP_contra_clockwise.bmp"); // Save new file 1
    std::cout << "-> Second task completed: file flip contra clockwise." << "\n";
    
    // Use filter Gausa for BMP contra clockwise
    ApplyGaussianFilter(new_bmp_file_1); 
    Save_BMP_File(new_bmp_file_1, "BMP_contra_clockwise_filter.bmp"); // Save result filter Gausa
    
    // Free memory
    Free_BMP_File(new_bmp_file_1);
    std::cout << "Memory free." << "\n\n";

    // Flip BMP clockwise
    BMP_File* new_bmp_file_2 = flip_BMP_90_clockwise(bmp_file);
    Save_BMP_File(new_bmp_file_2, "BMP_clockwise.bmp"); // Save new file 2
    std::cout << "-> Third task completed: file flip clockwise." << "\n";

    // Use filter Gausa for BMP contra clockwise
    ApplyGaussianFilter(new_bmp_file_2); 
    Save_BMP_File(new_bmp_file_2, "BMP_clockwise_filter.bmp"); // Save result filter Gausa
    
    std::cout << "Save result filter Gausa" << "\n";
    std::cout << "-> Fourth task completed: used filter Gausa for fliping BMP file" << "\n\n";
    
    // Free memory
    Free_BMP_File(new_bmp_file_2);
    std::cout << "Memory free." << "\n\n";
    
    // Free memory for original imagine
    Free_BMP_File(bmp_file);
    return 0;
}
