#ifndef QUANTIZER_H
#define QUANTIZER_H

#include <iostream>
#include "LPType.h"
#include "Image.h"


class Quantizer
{
public:
    explicit Quantizer(size_t width, size_t height)
    	: _width(width), _height(height)
	{
	    _rawsrc.reset(new unsigned char[4 * width * height]);
	    _rawdest.reset(new unsigned char[width * height]);
	    _src.reset(new unsigned char*[height]);
	    for (size_t i = 0; i < _height; ++i)
	    {
	        _src[i] = _rawsrc.get() + (i * width * 4);
	    }
	    _palette.reset(new png_color[256]);
	    _trans.reset(new unsigned char[256]);
	};
    virtual ~Quantizer() {}

    void process(rows_t src, bool hasAlphaChannel)
    {
        if (hasAlphaChannel)
	    {
	    	Image::copy_4_to_4(_width, _height, src, _src);
	    }
	    else
	    {
	    	Image::copy_3_to_4(_width, _height, src, _src);
	    }
	    _process();
	}
    void process(buffer_t src, bool hasAlphaChannel)
    {
        if (hasAlphaChannel)
	    {
	    	Image::copy_4_to_4(_width, _height, src, _rawsrc);
	    }
	    else
	    {
	    	Image::copy_3_to_4(_width, _height, src, _rawsrc);
	    }
	    _process();
	}
    buffer_t buffer()
    {
        return _rawdest;
    };
    palette_t palette()
    {
        return _palette;
    };
    trans_t trans()
    {
        return _trans;
    }

protected:
    rows_t _src;
    buffer_t _rawsrc;
    buffer_t _rawdest;
    size_t _width, _height;
    palette_t _palette;
    trans_t _trans;
    virtual void _process() {}
};

#endif