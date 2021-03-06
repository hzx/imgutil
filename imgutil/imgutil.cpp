#include <list>
#include <cstring>
#include <sstream>
#include <Magick++.h>
#include "imgutil.h"


using Magick::Image;
using Magick::Geometry;


void initLib() {
  Magick::InitializeMagick(NULL);
}


int resizeImage(string dest, string src, size_t width, size_t height) {
  // calculate size

  Image image;
  Geometry size(width, height);
  size.aspect(false);

  try {
    image.read(src);
  } catch (...) {
    return IMAGE_ERROR_READ;
  }

  if (image.size().width() > width or image.size().height() > height) {
    //image.resize(size);
    image.scale(size);
  }
  image.write(dest);

  return IMAGE_ERROR_OK;
}


/* int resizeGif(string dest, string src, size_t width, size_t height) { */
/*   std::list<Image> list; */ 
/*   Magick::readImages(&list, src); */

/*   Image image; */ 
/*   Geometry size(width, height); */
/*   size.aspect(false); */

/*   for (auto im: list) { */
/*     im.resize(size); */
/*   } */

/*   Magick::appendImages(&image, list.begin(), list.end()); */ 
/*   image.write(dest); */ 

/*   return IMAGE_ERROR_OK; */
/* } */


/* int resizeSmart(string dest, string src, size_t width, size_t height) { */
/*   string ext = getExtension(src); */

/*   if (ext.length() == 3) { */
/*     tolower(ext); */
/*     if (std::memcmp(ext.data(), "gif", 3) == 0) { */
/*       return resizeGif(dest, src, width, height); */
/*     } */
/*   } */

/*   return resizeImage(dest, src, width, height); */
/* } */


/* int resizeSmartBunch(string dest, string src, vector<size_t> sizes) { */
  /* if (sizes.size() % 2 != 0) return IMAGE_ERROR_SIZES; */

  /* string ext = getExtension(src); */
  /* int error; */

  /* if (ext.length() == 3) { */
  /*   tolower(ext); */
  /*   if (std::memcmp(ext.data(), "gif", 3) == 0) { */
  /*     for (int i = 0, length = sizes.size(); i < length; i += 2) { */
  /*       error = resizeGif( */
  /*           std::to_string(sizes[i]) + 'x' + std::to_string(sizes[i+1]) + dest, */
  /*           src, sizes[i], sizes[i+1]); */

  /*       if (error != IMAGE_ERROR_OK) { */
  /*         return error; */
  /*       } */
  /*     } */

  /*     return IMAGE_ERROR_OK; */
  /*   } */
  /* } */

  /* for (int i = 0, length = sizes.size(); i < length; i += 2) { */
  /* } */

  /* return IMAGE_ERROR_OK; */

  /* return IMAGE_ERROR_SIZES; */
/* } */


int resizeThumb(string dest, string src, size_t width, size_t height) {
  Image image;

  try {
    image.read(src);
  } catch (...) {
    return IMAGE_ERROR_READ;
  }

  // image width and height
  size_t iw = image.size().width();
  size_t ih = image.size().height();

  // not resize small image
  /* if (iw < width or ih < height) { */
  /*   return IMAGE_ERROR_SMALLER; */
  /* } */

  // find new big size for resize
  size_t bw, bh;

  // image ratio
  float ir = static_cast<float>(iw) / static_cast<float>(ih);
  // thumb ratio
  float tr = static_cast<float>(width) / static_cast<float>(height);

  if (ir > tr) { // image width greather than thumb width
    bw = ir * height;
    bh = height; // use thumb height
  } else { // image height greater than thumb height
    bw = width; // use thumb width
    bh = width / ir;
  }

  // resize image with thumb size
  Geometry bs(bw, bh);
  bs.aspect(false);

  image.scale(bs);
  //image.resize(bs);

  // calculate crop offsets
  size_t xoffset;
  size_t yoffset;
  if (ir > tr) {
    xoffset = (bw - width) / 2;
    yoffset = 0;
  } else {
    xoffset = 0;
    yoffset = (bh - height) / 2;
  }

  // crop image
  image.crop(Geometry(width, height, xoffset, yoffset));

  image.write(dest);

  return IMAGE_ERROR_OK;
}


std::string createFilename(std::string path, std::string filename,
    size_t width, size_t height) {
  std::ostringstream buf;

  buf << path << width << 'x' << height << '-' << filename;

  return buf.str();
}
