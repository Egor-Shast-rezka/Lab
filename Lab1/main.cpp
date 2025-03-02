/*
    Egor Shastin st129457@student.spbu.ru
    This code is a general in all project, it run program and print commits.
*/

#include "bmp_reader.h"
#include "filter_gaus.h"
#include <iostream>

int main(int argc, char* argv[]) {

    // Check heving two arguments
    if (argc < 2)
    {
        std::cout << "Using: " << argv[0] << " <path to BMP file>" << "\n"; // If the file path is not specified
        return 0;
    }

    BMP_File bmp_file;
    if (!bmp_file.Load_BMP_File(argv[1]))  // Create array for BMP imagine
    {
        std::cerr << "Failed to load BMP file." << "\n";
        return -1;
    }
    else
    {
        std::cout << "BMP File read succesful." << "\n";
    }
    
    
    std::cout << "BMP file size:" << bmp_file.bmp_header.file_size << " byte" << "\n";
    std::cout << "-> First task completed: file size printed." << "\n\n";
    
    // Flip BMP contra clockwise
    auto new_bmp_file_1 = bmp_file.flip_BMP_90_contra_clockwise();
    new_bmp_file_1->Save_BMP_File("BMP_contra_clockwise.bmp"); // Save new file 1
    std::cout << "-> Second task completed: file flip contra clockwise." << "\n";

    // Use filter Gausa for BMP contra clockwise
    ApplyGaussianFilter(new_bmp_file_1.get(), 5, 3.0);
    new_bmp_file_1->Save_BMP_File("BMP_contra_clockwise_filter.bmp"); // Save result filter Gausa
    new_bmp_file_1.reset(); // Delete new_bmp_file_1
    
    // Flip BMP clockwise
    auto new_bmp_file_2 = bmp_file.flip_BMP_90_clockwise();
    new_bmp_file_2->Save_BMP_File("BMP_clockwise.bmp"); // Save new file 2
    std::cout << "-> Third task completed: file flip clockwise." << "\n";

    // Use filter Gausa for BMP clockwise
    ApplyGaussianFilter(new_bmp_file_2.get(), 5, 3.0);
    new_bmp_file_2->Save_BMP_File("BMP_clockwise_filter.bmp"); // Save result filter Gausa
    new_bmp_file_2.reset(); // Delete new_bmp_file_2
    
    std::cout << "Save result filter Gausa" << "\n";
    std::cout << "-> Fourth task completed: used filter Gausa for fliping BMP file" << "\n\n";

    return 0;
}
