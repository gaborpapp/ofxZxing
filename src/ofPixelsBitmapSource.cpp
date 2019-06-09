#include "ofPixelsBitmapSource.h"

namespace zxing {

ofPixelsBitmapSource::ofPixelsBitmapSource(ofPixels& pixels) :
	LuminanceSource( pixels.getWidth(), pixels.getHeight() ),
	image_(pixels)
{
  width = pixels.getWidth();
  height = pixels.getHeight();
  pixel_cache = pixels.getData();
}

ofPixelsBitmapSource::~ofPixelsBitmapSource() {

}

int ofPixelsBitmapSource::getWidth() const {
  return width;
}

int ofPixelsBitmapSource::getHeight() const {
  return height;
}

zxing::ArrayRef<char> ofPixelsBitmapSource::getRow(int y, zxing::ArrayRef<char> row) const {
	if (!row) {
		row = zxing::ArrayRef<char>(width);
	}
	for (int x = 0; x < width; x++) {
		const unsigned char* p = &pixel_cache[3 * (y * width + x)];
		row[x] = (unsigned char)((
					306 * (int)(*p) +
					601 * (int)(*(p+1)) +
					117 * (int)(*(p+2)) + 0x200) >> 10);
		p += 3;
	}
	return row;
}

zxing::ArrayRef<char> ofPixelsBitmapSource::getMatrix() const {
	int width = getWidth();
	int height =  getHeight();
	const char* p = (const char *)(&pixel_cache[0]);
	zxing::ArrayRef<char> matrix(width * height);
	char* m = &matrix[0];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*m= (unsigned char)((
				306 * (int)(*p) +
				601 * (int)(*(p+1)) +
				117 * (int)(*(p+2)) + 0x200) >> 10);
			m++;
			p += 3;
		}
	}
	return matrix;
}

bool ofPixelsBitmapSource::isRotateSupported() const {
  return false;
}

Ref<LuminanceSource> ofPixelsBitmapSource::rotateCounterClockwise() const {
  return Ref<ofPixelsBitmapSource> (NULL);
}

}

