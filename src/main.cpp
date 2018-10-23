#include <iostream>

#include "raytracer.h"

raytracer rayTracer;

int main(int argv, char *argc[]) {

    if(argv == 1) {
        rayTracer.setAppName(argc[0]);
        rayTracer.main();
    } else {
        rayTracer.main(argv, argc);
    }

    return 0;
}
