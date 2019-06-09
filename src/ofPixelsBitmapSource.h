#pragma once

#include "zxing/LuminanceSource.h"
#include "ofPixels.h"

namespace zxing {

// modeled off the Image Magick demo
class ofPixelsBitmapSource : public LuminanceSource {
private:
  ofPixels& image_;
  int width;
  int height;
  const unsigned char* pixel_cache;

public:
  ofPixelsBitmapSource(ofPixels& image);

  ~ofPixelsBitmapSource();

  int getWidth() const;
  int getHeight() const;
  zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const;
  zxing::ArrayRef<char> getMatrix() const;
  bool isRotateSupported() const;
  Ref<LuminanceSource> rotateCounterClockwise() const;
};

}
