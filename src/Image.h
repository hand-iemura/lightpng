#ifndef IMAGE_H
#define IMAGE_H

#include "LPType.h"

class Image
{
public:
    size_t width() const throw() { return _width; }
    size_t height() const throw() { return _height; }
    rows_t image() const { return _rows; }
    buffer_t buffer() const { return _data; }

    virtual bool hasAlpha() const { return false; }
    virtual bool hasAlphaChannel() const { return false; }

    operator void*() const { return _valid ? const_cast<Image*>(this) : 0; }
    bool operator!() const { return !_valid; }
    bool valid() const { return _valid; }

    virtual ~Image() {}

    static void copy_4_to_4(size_t width, size_t height, buffer_t& src, buffer_t& dest)
    {
        memcpy(dest.get(), src.get(), height * width * 4);
    }
    static bool copy_4_to_4(size_t width, size_t height, buffer_t& src, buffer_t& dest, bool clean)
    {
        bool result = false;
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                size_t offset = (y * width + x) * 4;
                if (src[offset + 3] == 0)
                {
                    result = result || (src[offset] != 0) || (src[offset + 1] != 0) || (src[offset + 2] != 0);
                    dest[offset] = 0;
                    dest[offset + 1] = 0;
                    dest[offset + 2] = 0;
                    dest[offset + 3] = 0;
                }
                else
                {
                    dest[offset]     = src[offset];
                    dest[offset + 1] = src[offset + 1];
                    dest[offset + 2] = src[offset + 2];
                    dest[offset + 3] = src[offset + 3];
                }
            }
        }
        return result;
    }
    static void copy_4_to_4(size_t width, size_t height, rows_t& src, rows_t& dest)
    {
        for (size_t y = 0; y < height; ++y)
        {
            memcpy(dest[y], src[y], width * 4);
        }
    }
    static void copy_4_to_3(size_t width, size_t height, buffer_t& src, buffer_t& dest)
    {
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                size_t offset1 = (y * width + x) * 3;
                size_t offset2 = (y * width + x) * 4;
                dest[offset1]     = src[offset2];
                dest[offset1 + 1] = src[offset2 + 1];
                dest[offset1 + 2] = src[offset2 + 2];
            }
        }
    }
    static void copy_4_to_3(size_t width, size_t height, rows_t& src, rows_t& dest)
    {
        for (size_t y = 0; y < height; y++)
        {
            unsigned char* destline = dest[y];
            unsigned char* srcline = src[y];
            for (size_t x = 0; x < width; x++)
            {
                destline[x * 3]     = srcline[x * 4];
                destline[x * 3 + 1] = srcline[x * 4 + 1];
                destline[x * 3 + 2] = srcline[x * 4 + 2];
            }
        }
    }
    static void copy_3_to_4(size_t width, size_t height, buffer_t& src, buffer_t& dest)
    {
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                size_t src_offset = (y * width + x) * 3;
                size_t dest_offset = (y * width + x) * 4;
                dest[dest_offset]     = src[src_offset];
                dest[dest_offset + 1] = src[src_offset + 1];
                dest[dest_offset + 2] = src[src_offset + 2];
                dest[dest_offset + 3] = 255;
            }
        }
    }
    static void copy_3_to_4(size_t width, size_t height, rows_t& src, rows_t& dest)
    {
        for (size_t y = 0; y < height; y++)
        {
            unsigned char* destline = dest[y];
            unsigned char* srcline = src[y];
            for (size_t x = 0; x < width; x++)
            {
                destline[x * 4]     = srcline[x * 3];
                destline[x * 4 + 1] = srcline[x * 3 + 1];
                destline[x * 4 + 2] = srcline[x * 3 + 2];
                destline[x * 4 + 3] = 255;
            }
        }
    }
    static void copy_3_to_3(size_t width, size_t height, rows_t& src, rows_t& dest)
    {
        for (size_t i = 0; i < height; ++i)
        {
            memcpy(dest[i], src[i], width * 3);
        }
    }
protected:
    explicit Image() : _width(0), _height(0), _valid(false) {}

    void alloc(size_t pixelBytes)
    {
        _data.reset(new unsigned char[pixelBytes * _width * _height]);
        _rows.reset(new unsigned char*[_height]);
        for (size_t i = 0; i < _height; ++i)
        {
            _rows[i] = _data.get() + (i * _width * pixelBytes);
        }
    }
    buffer_t _data;
    rows_t _rows;
    size_t _width, _height;
    bool _valid;
};

#endif
