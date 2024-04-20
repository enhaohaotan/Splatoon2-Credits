#ifndef COLOR_H
#define COLOR_H

namespace Color {
    struct RGB
    {
        float r;  // Red: 0-1
        float g;  // Green: 0-1
        float b;  // Blue: 0-1
    };

    struct HSV
    {
        float h;  // Hue: 0-360 degrees
        float s;  // Saturation: 0-1
        float v;  // Value: 0-1
    };

    RGB HSVtoRGB(const HSV& hsv);
}

#endif //COLOR_H
