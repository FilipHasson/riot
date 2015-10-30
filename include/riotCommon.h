#ifndef RIOT_COMMON
#define RIOT_COMMON

#define MINX 80
#define MINY 24

/* InmateType will allow for a bidirectional equivalence between unit types and
   their associated char values.*/
enum InmateType {
    homeboy = 'h',
    bruiser = 'b',
    lunatic = 'l',
    fatty = 'f',
    speedy = 's',
    cutie = 'c',
    attorney = 'a',
    doctor = 'd'
};

enum GuardType {
    guard,
    dogs,
    lunchlady,
    psychiatrist,
    shartshooter,
    warder,
    cyborg
};

enum AI {
    prox, //proximity
    aoe, //area of effect
    end //closest to end
};

enum Colour {
    GREEN,
    YELLOW,
    ORANGE,
    RED
};

#endif
