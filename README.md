# Lab1 and add Multithreading.
Егор Шастин Олегович, gruppa b81-mm
Contact: st129457@student.spbu.ru,egor.shast0.0@gmail.com

## Overview

This project delivers a comprehensive set of C++ tools for efficient BMP image manipulation, encompassing core functionalities like loading, saving, 90-degree rotations (both clockwise and counter-clockwise), and applying a Gaussian blur filter. The implementation leverages multithreading to optimize performance for image processing tasks, making it suitable for handling larger images more efficiently.

## Table of Contents
- [Installation and Build](#installation-and-build)
- [Tests](#tests)

## Installation and Build

### Building the Project

```sh
make
```

### Running the Decoder
To start the programm, run the compiled executable:

```sh
make
./bin/read_BMP <path to BMP file>    # To start the program with your bmp-file
```

or

```sh
make
make run    # To start the program with 'example.bmp'
```

## Tests

#### Continuous Integration (CI)
This project uses GitHub Actions for automated builds and testing. All tests are run in the CI pipeline on every commit.

#### Running Tests Locally
To run tests locally, you can use the following commands:

```sh
make
make test    # Runs tests for all programm
```

