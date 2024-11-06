/*

*/

#include "bmp_reader.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Check heving two arguments
    if (argc < 2) {
        std::cout << "Using: " << argv[0] << " <path to BMP file>" << "\n"; // If the file path is not specified
        return 0;
    }

    BMP_File* bmpf = Load_BMP_File(argv[1]); // Create array for BMP imagine
    
    if (bmpf) {
        std::cout << "BMP file size:" << bmpf->bmp_header.file_size << " byte" << "\n";
        std::cout << "Width:" << bmpf->dib_header.width << " pixels" << "\n";
        std::cout << "Height:" << bmpf->dib_header.height << " pixels" <<  "\n";
        Free_BMP_File(bmpf); // Freeing up memory
    }

    return 0;
}
