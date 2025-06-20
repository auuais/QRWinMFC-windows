#pragma once

#include "QrExport.hxx"

namespace QrSDK
{
    EXTERNC
    {
        struct QrPoint
        {
            int x; int y;
        };

        struct QrPoint2Df
        {
            float x; float y;
        };

        struct QrSize
        {
            int width; int height;
        };

        struct QrRect
        {
            int x, y, width, height;

            QrRect() { x = 0; y = 0; width = 0; height = 0; };
            QrRect(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) { };
        };

        struct QrLocItem
        {
            int x; int y;
            double value;
        };

        //typedef struct QrVec2b { uchar val[2]; } CvVec2b;
        //typedef struct QrVec3b { uchar val[3]; } CvVec3b;
        //typedef struct QrVec4b { uchar val[4]; } CvVec4b;
        //typedef struct QrVec6b { uchar val[6]; } CvVec6b;
        //typedef struct QrVec2s { short val[2]; } CvVec2s;
        //typedef struct QrVec3s { short val[3]; } CvVec3s;
        //typedef struct QrVec4s { short val[4]; } CvVec4s;
        //typedef struct QrVec6s { short val[6]; } CvVec6s;
        //typedef struct QrVec2w { ushort val[2]; } CvVec2w;
        //typedef struct QrVec3w { ushort val[3]; } CvVec3w;
        //typedef struct QrVec4w { ushort val[4]; } CvVec4w;
        //typedef struct QrVec6w { ushort val[6]; } CvVec6w;
        //typedef struct QrVec2i { int val[2]; } CvVec2i;
        //typedef struct QrVec3i { int val[3]; } CvVec3i;
        //typedef struct QrVec4i { int val[4]; } CvVec4i;
        //typedef struct QrVec6i { int val[6]; } CvVec6i;
        //typedef struct QrVec2f { float val[2]; } CvVec2f;
        //typedef struct QrVec3f { float val[3]; } CvVec3f;
        //typedef struct QrVec4f { float val[4]; } CvVec4f;
        //typedef struct QrVec6f { float val[6]; } CvVec6f;
        //typedef struct QrVec2d { double val[2]; } CvVec2d;
        //typedef struct QrVec3d { double val[3]; } CvVec3d;
        //typedef struct QrVec4d { double val[4]; } CvVec4d;
        //typedef struct QrVec6d { double val[6]; } CvVec6d;
    }
}


