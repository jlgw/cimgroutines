#include "houghcirc.h"
#include <vector>
#include "CImg.h"
#include <iostream>
#include <sstream>

using namespace cimg_library;
int main(int argc, char *argv[]){
    if(argc!=6){
        std::cout << "usage: " << argv[0] << " <inputfilename> <minradius>"
        << " <maxradius> <threshold> <outputfilename>" << std::endl;
        return 1;
    }
    
    CImg<unsigned char> image(argv[1]);
    int rmin, rmax, threshold;
    std::istringstream ss1(argv[2]);
    ss1>>rmin;
    std::istringstream ss2(argv[3]);
    ss2>>rmax;
    std::istringstream ss3(argv[4]);
    ss3>>threshold;
    int width = image.width();
    int height = image.height();
    CImg<unsigned char> outp(width, height, 1, 1, 0);
    std::vector<int> circles = fn(image, rmin, rmax, threshold);
    const int white[] = {255};
    int x, y, r;
    std::vector<int>::iterator it = circles.begin();
    while(it!=circles.end()){
        x = *(it++);
        y = *(it++);
        r = *(it++);
        std::cout << "Circle found at " << x << "," << y << " radius " << r << std::endl;
        outp.draw_circle(x,y,r,white,1,1);
    }
    outp.save(argv[5]);
}
