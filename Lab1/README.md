# Lab1 and add Multithreading.
Егор Шастин Олегович, gruppa b81-mm
Contact: st129457@student.spbu.ru,egor.shast0.0@gmail.com

## Overview

...

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
./bin/read_BMP <path to BMP file>
```

or

```sh
make
make run # Run program
```

## Tests

#### Continuous Integration (CI)
This project uses GitHub Actions for automated builds and testing. All tests are run in the CI pipeline on every commit.

#### Running Tests Locally
To run tests locally, you can use the following commands:

```sh
make run-test    # Runs tests for all programm
```

