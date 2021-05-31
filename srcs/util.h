#include <iostream>
#include <vector>

#define SUNNY 0
#define FOGGY 1
#define RAINY 2

class Viterbi {
public:
    // probability from today's weather to each weather tomorrow
    double weather_trans_matrix[3][3];
    // in each weather, probability of wearing 
    double emission_matrix[3][2];
    // initial probability of weather in first day 
    double init_weather_p[3];

    Viterbi();
};