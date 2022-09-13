
#include <string>
#include <cstring>
#include <iostream>

#include "Painter.h"
#include "db.h"

namespace gui {

using namespace cimg_library;
using namespace db;

Painter::Painter()
{
    R = 2;
}
Painter::Painter(int x, int y)
{
    setWindow(800, 800);
    setBackground(x, y);

    R = 2;
}

void Painter::setWindow(int x, int y)
{
    MAX_BG_X = x;
    MAX_BG_Y = y;
}

void Painter::setBackground(int x, int y)
{
    scaleX = (double)MAX_BG_X / x;
    scaleY = (double)MAX_BG_Y / y;

    //x, y, z, c, pixel init
    bg = new CImg<unsigned char>(MAX_BG_X, MAX_BG_Y, 1, 3, 255);
    bg->draw_rectangle(0, 0, MAX_BG_X, MAX_BG_Y, white);
    img = new CImg<unsigned char>(*bg);
    //window = new CImgDisplay(MAX_BG_X, MAX_BG_Y, "Title");
}

void Painter::destroy()
{
    delete bg;
    delete img;
    //delete window;
}

void Painter::drawPoint(int x, int y, Color color)
{
    img->draw_circle((int)(scaleX*x), (int)(scaleY*y), R, color, 0.5);
}

void Painter::drawCentroid(int x, int y, Color color)
{
    img->draw_circle((int)(scaleX*x), (int)(scaleY*y), 3, color);
}

void Painter::drawPoint(Point p, Color color)
{
    drawPoint(p.getX(), p.getY(), color);
}

void Painter::drawLine(int x1, int y1, int x2, int y2, Color color)
{
    img->draw_line((int)(scaleX*x1), (int)(scaleY*y1), (int)(scaleX*x2), (int)(scaleY*y2), color);
}

void Painter::show()
{
    img->display(*window);
    while(!window->is_closed() && !window->is_keyESC())
        wait(window);
}

void Painter::clear()
{
    img->clear();
}

void Painter::save_png(std::string fileName)
{
    img->save_png(fileName.c_str());
}

}
