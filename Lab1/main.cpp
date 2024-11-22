/*
    Egor Shastin st129457@student.spbu.ru
    This code is a general in all project, it run program and print commits.
*/

#include "bmp_reader.h"
#include "filter_gaus.h"
#include <iostream>
#include <memory>

// The program reads an image called example.bmp
int main(int argc, char* argv[])
{
    // Check heving two arguments
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path to BMP file>" << "\n"; // If the file path is not specified
        return 0;
    }

    // Load BMP file using std::unique_ptr
    std::unique_ptr<BMP_File> bmp_file = Load_BMP_File(argv[1]);

    if (!bmp_file)
    {
        std::cerr << "Failed to load BMP file." << "\n";
        return -1;
    }

    std::cout << "BMP File read successfully.\n";
    std::cout << "BMP file size: " << bmp_file->bmp_header.file_size << " bytes\n";
    std::cout << "-> First task completed: file size printed.\n\n";

    // Flip BMP contra clockwise
    std::unique_ptr<BMP_File> new_bmp_file_1(flip_BMP_90_contra_clockwise(bmp_file.get()));
    Save_BMP_File(new_bmp_file_1.get(), "BMP_contra_clockwise.bmp");
    std::cout << "-> Second task completed: file flipped contra-clockwise." << "\n";
    
    
    // Use filter Gausa for BMP contra clockwise
    ApplyGaussianFilter(new_bmp_file_1.get(), 5, 2.0);
    Save_BMP_File(new_bmp_file_1.get(), "BMP_contra_clockwise_filter.bmp"); // Save result filter Gausa
    std::cout << "-> Gaussian filter applied to contra-clockwise BMP." << "\n";
    
    
    // Flip BMP clockwise
    std::unique_ptr<BMP_File> new_bmp_file_2(flip_BMP_90_clockwise(bmp_file.get()));
    Save_BMP_File(new_bmp_file_2.get(), "BMP_clockwise.bmp"); // Save new file 2
    std::cout << "-> Third task completed: file flipped clockwise." << "\n";
    
    // Use filter Gausa for BMP contra clockwise
    ApplyGaussianFilter(new_bmp_file_2.get(), 5, 2.0);
    Save_BMP_File(new_bmp_file_2.get(), "BMP_clockwise_filter.bmp"); // Save result filter Gausa
    std::cout << "-> Gaussian filter applied to clockwise BMP." << "\n\n";
    
    std::cout << "Save result filter Gausa" << "\n";
    std::cout << "-> Fourth task completed: used filter Gausa for fliping BMP file" << "\n\n";

    return 0;
}
