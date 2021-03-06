#ifndef IMGUTIL_H
#define IMGUTIL_H


#include <string>
#include <vector>


using std::string;
using std::vector;


const int IMAGE_ERROR_OK = 0;
const int IMAGE_ERROR_READ = 1;
const int IMAGE_ERROR_SIZES = 2;
const int IMAGE_ERROR_SMALLER = 3;

void initLib();

// resize src image to width, height size
// rationWidth - save ratio by width, real height not equal to height
// or save ratio by height, real width not equal to width
// return error code
int resizeImage(string dest, string src, size_t width, size_t height);
/* int resizeGif(string dest, string src, size_t width, size_t height); */
/* int resizeSmart(string dest, string src, size_t width, size_t height); */
/* int resizeSmartBunch(string dest, string src, vector<size_t> sizes); */
int resizeThumb(string dest, string src, size_t width, size_t height);

std::string createFilename(std::string path, std::string filename,
    size_t width, size_t height);


#endif /* end of include guard: IMGUTIL_H */
