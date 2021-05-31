#include "util.h"

Viterbi::Viterbi() {
    // initial weather_trans_matrix
    weather_trans_matrix[SUNNY][SUNNY] = 0.8;
    weather_trans_matrix[SUNNY][FOGGY] = 0.15;
    weather_trans_matrix[SUNNY][RAINY] = 0.05;
    weather_trans_matrix[FOGGY][SUNNY] = 0.2;
    weather_trans_matrix[FOGGY][FOGGY] = 0.5;
    weather_trans_matrix[FOGGY][RAINY] = 0.3;
    weather_trans_matrix[RAINY][SUNNY] = 0.2;
    weather_trans_matrix[RAINY][FOGGY] = 0.2;
    weather_trans_matrix[RAINY][RAINY] = 0.6;
    // initial emission_matrix
    emission_matrix[SUNNY][0] = 0.9;
    emission_matrix[SUNNY][1] = 0.1;
    emission_matrix[FOGGY][0] = 0.7;
    emission_matrix[FOGGY][1] = 0.3;
    emission_matrix[RAINY][0] = 0.2;
    emission_matrix[RAINY][1] = 0.8;
    // initial init_weather_p
    init_weather_p[SUNNY] = 0.5;
    init_weather_p[FOGGY] = 0.25;
    init_weather_p[RAINY] = 0.25;
}