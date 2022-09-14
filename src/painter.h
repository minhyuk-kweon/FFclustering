#pragma once

#include "CImg.h"
#include "db.h"

namespace gui {
		
static const unsigned char white[]  = {255, 255, 255},
                           black[]  = {  0,   0,   0},
                           red[]    = {255,   0,   0},
                           blue[]   = {120, 200, 255},
                           green[]  = {  0, 255,   0},
                           purple[] = {255, 100, 255},
                           orange[] = {255, 165,   0},
                           yellow[] = {255, 255,   0};

using namespace cimg_library;
using namespace db;

typedef const unsigned char* Color;

class Painter
{
public:
    Painter();
    Painter(int x, int y);
	//~Painter();

	void show();
    void clear();
    void destroy();
    void save_png(std::string fileName);

    void setWindow(int x, int y);
    void setBackground(int x, int y);

	void drawPoint(int x, int y, Color color);
	void drawCentroid(int x, int y, Color color);
	void drawPoint(Point p, Color color);
	void drawLine(int x1, int y1, int x2, int y2, Color color);

private:
    // point, line
    // point circle radius
    int R;

    //background
    int MAX_BG_X, MAX_BG_Y;

	// Scaling Ratio
    double scaleX, scaleY;

	CImg<unsigned char>* bg;
	CImg<unsigned char>* img;
	CImgDisplay* window;
};


}
