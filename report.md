# Multithreading Optimization Report

## Goal

Compare image filtering performance before and after adding multithreading to a C++ program.

## Results

### Before adding multithreading:

```
BMP File read succesful.
BMP file size:818058 byte
-> First task completed: file size printed.

Image saved successfully to BMP_contra_clockwise.bmp
-> Second task completed: file flip contra clockwise.
Filter time: 0.0753097 seconds
Image saved successfully to BMP_contra_clockwise_filter.bmp
Image saved successfully to BMP_clockwise.bmp
-> Third task completed: file flip clockwise.
Filter time: 0.0712197 seconds
Image saved successfully to BMP_clockwise_filter.bmp
Save result filter Gausa
-> Fourth task completed: used filter Gausa for fliping BMP file
```


### After adding multithreading:

```
BMP File read succesful.
BMP file size:818058 byte
-> First task completed: file size printed.

Image saved successfully to BMP_contra_clockwise.bmp
Image saved successfully to BMP_contra_clockwise.bmp
-> Second task completed: file flip contra clockwise.
Filter time: 0.0435408 seconds
Image saved successfully to BMP_contra_clockwise_filter.bmp
Image saved successfully to BMP_clockwise.bmp
-> Third task completed: file flip clockwise.
Filter time: 0.0209065 seconds
Image saved successfully to BMP_clockwise_filter.bmp
Save result filter Gausa
-> Fourth task completed: used filter Gausa for fliping BMP file
```


## Output

After the introduction of multithreading:
- The filtering time has decreased:
- for the first image from `0.0753s` to `0.0435s`
  - for the second image, from `0.0712s` to `0.0209s`
- Performance improved due to parallel processing line by line.

Multithreading significantly speeds up image filtering, especially when increasing their size.
