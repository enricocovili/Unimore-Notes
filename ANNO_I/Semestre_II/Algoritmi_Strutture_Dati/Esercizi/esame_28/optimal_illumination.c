//
// Created by enri on 5/25/24.
//

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

extern bool isAllIlluminated(const bool* road, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (road[i] == false)
            return false;
    }
    return true;
}

extern int countLightsOn(const bool* lights, size_t size) {
    int counter = 0;
    for (size_t i = 0; i < size; i++) {
        if (lights[i] == true)
            counter++;
    }
    return counter;
}

extern void OptimalIlluminationRec(
        int M, int R,
        bool* currLight, bool* currRoad, int* best, bool* bestLight, size_t level,
        const int *light, size_t light_size)
        {
    if (level >= light_size) {
        if (!isAllIlluminated(currRoad, M)) {
            return;
        }
        int lights = countLightsOn(currLight, light_size);
        if (*best == -1 || lights < *best) {
            *best = lights;
            memmove(bestLight, currLight, sizeof(bool)*light_size);
        }
        return;
    }
    // spento
    bool *beforeOn = calloc(M, sizeof(bool));
    memmove(beforeOn, currRoad, M*sizeof(bool));
    OptimalIlluminationRec(M, R, currLight, currRoad, best, bestLight, level+1, light, light_size);
    // accendo
    currLight[level] = true;
    for (int i = light[level]-R; i <= light[level]+R; i++) {
        if (i < 0 || i >= M)
            continue;
        currRoad[i] = true;
    }
    OptimalIlluminationRec(M, R, currLight, currRoad, best, bestLight, level+1, light, light_size);
    // spengo ora
    currLight[level] = false;
    memmove(currRoad, beforeOn, M*sizeof(bool));
    free(beforeOn);
}

extern bool* OptimalIllumination(int M, int R, const int *light,
                                 size_t light_size) {
    bool* currLight = calloc(light_size, sizeof(bool));
    bool* currRoad = calloc(light_size*2, sizeof(bool));
    bool* bestLight = calloc(light_size, sizeof(bool));
    int* fixedLight = calloc(light_size, sizeof(bool));
    for (size_t i=0; i<light_size; i++) {
        fixedLight[i] = light[i]*2;
    }
    int nBestLight = -1;
    OptimalIlluminationRec(M*2+1, R*2, currLight, currRoad, &nBestLight, bestLight, 0, fixedLight, light_size);
    free(currLight);
    free(currRoad);
//    free(bestLight);
    return bestLight;
}

//int main(void) {
//    int light[3] = {2,7,9};
//    bool* res = OptimalIllumination(10, 3, light, 3);
//    free(res);
//    return 0;
//}