#include "CImg.h"
#include <math.h>
#include <vector>
#include <iostream>

#define MAX_RADIUS 500
#define STEP_CIRCLES 10000

using namespace cimg_library;

int indmax(int *v, int maxind){
    int max = 0;
    int indmax = 0;
    for(int i=0; i<maxind; i++){
        if(v[i]>max){
            max = v[i];
            indmax = i;
        }
    }
    return indmax;
}

float dist(int x1, int y1, int x2, int y2){
    return std::sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

std::vector<int> fn(CImg<unsigned char> img, int min_radius,
        int max_radius, int threshold){
    std::vector<int> outv;
    outv.reserve(STEP_CIRCLES);
    int radius_array[MAX_RADIUS]; //This is faster to search
    int width = img.width();
    int height = img.height();
    int xmin, xmax, ymin, ymax;
    int x1, x2, y1, y2;
    int r, im, v;
    CImg<unsigned char> vote(width, height, 2*max_radius, 1, 0);
    cimg_forXY(img, x1, y1){
        xmin = std::max(x1-max_radius, 0);
        xmax = std::min(x1+max_radius, width);
        ymin = std::max(y1-max_radius, 0);
        ymax = std::min(y1+max_radius, height);
        std::memset(radius_array, 0, max_radius*sizeof(int));
        for(x2=xmin; x2<xmax; x2++){
            for(y2=ymin; y2<ymax; y2++){
                if(((int)img(x2,y2))==0){
                    continue;
                }
                r = (int)(dist(x1, y1, x2, y2)+0.5);
                radius_array[r]++;
                vote(x1, y1, r, 0)++;
            }
        }
        im = indmax(&radius_array[min_radius], max_radius-min_radius)+min_radius;
        if(radius_array[im]>threshold){
            vote(x1,y1,0,0) = radius_array[im];
        }
    }
    CImg<unsigned char> I(5,5);
    cimg_for5x5(vote, x1, y1,0,0,I,unsigned char){
        if(vote(x1,y1)<threshold){
            continue;
        }
        if((int)I.max()==(int)(vote(x1,y1))){
            for(r=min_radius; r<max_radius; r++){
                //This part is allowed to be slow, it occurs infrequently
                v = (int)vote(x1, y1, r, 0);
                if(v>threshold){
                    //Exception handler for too many elements here
                    if((v>=(int)vote(x1,y1,r-1,0))&&(v>(int)vote(x1,y1,r+1,0))){
                        outv.push_back(x1);
                        outv.push_back(y1);
                        outv.push_back(r);
                    }
                }
            }
        }
    }
    return outv;
}
