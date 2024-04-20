#include "color.h"

namespace Color {
    RGB HSVtoRGB(const HSV& hsv) {
        RGB rgb{};
        float h = hsv.h, s = hsv.s, v = hsv.v;

        int i = int(h / 60.0f) % 6;
        float f = (h / 60.0f) - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - f * s);
        float t = v * (1.0f - (1.0f - f) * s);

        switch (i) {
            case 0: rgb.r = v; rgb.g = t; rgb.b = p; break;
            case 1: rgb.r = q; rgb.g = v; rgb.b = p; break;
            case 2: rgb.r = p; rgb.g = v; rgb.b = t; break;
            case 3: rgb.r = p; rgb.g = q; rgb.b = v; break;
            case 4: rgb.r = t; rgb.g = p; rgb.b = v; break;
            case 5: rgb.r = v; rgb.g = p; rgb.b = q; break;
        }

        return rgb;
    }
}
