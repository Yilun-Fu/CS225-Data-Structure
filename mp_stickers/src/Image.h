/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
using cs225::HSLAPixel;
using cs225::PNG;



class Image: public PNG{
    public:
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void rotateColor(double degrees);
    void illinify ();
    void grayscale ();
    void scale (double factor);
	void scale (unsigned w, unsigned h);
};
