#include "simon.h"

inline uint8_t lerpf(uint8_t a, uint8_t b, float t) {
    return (uint8_t)(a + (b - a) * t);
}

Color colorFromHex(uint32_t hex) {
    // if any hex value is invalid, return black
    if (hex > 0xffffffff) return BLACK;

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
