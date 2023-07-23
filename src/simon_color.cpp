#include "simon.h"

#define lerpf(a, b, t) ((a) + ((b) - (a)) * (t))

Color colorFromHex(uint32_t hex) {
    return {
        static_cast<unsigned char>((hex >> 24) & 0xff),
        static_cast<unsigned char>((hex >> 16) & 0xff),
        static_cast<unsigned char>((hex >> 8) & 0xff),
        static_cast<unsigned char>(hex & 0xff)
    };
}

Color colorLerp(Color a, Color b, float t) {
    return {
        (uint8_t)lerpf(a.r, b.r, t),
        (uint8_t)lerpf(a.g, b.g, t),
        (uint8_t)lerpf(a.b, b.b, t),
        (uint8_t)lerpf(a.a, b.a, t)
    };
}
