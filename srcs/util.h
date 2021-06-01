#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdint>

#define SUNNY 0
#define FOGGY 1
#define RAINY 2

class Viterbi {
public:
    int predict_days;
    std::vector<bool> observed_wearing;
    // record previous possible weather
    std::vector< std::vector<int> > back_record;
    std::vector< std::vector<double> > delta;
    // probability from today's weather to each weather tomorrow
    double weather_trans_matrix[3][3];
    // in each weather, probability of wearing 
    double emission_matrix[3][2];
    // initial probability of weather in first day 
    double init_weather_p[3];
    std::vector<int> ground_truth;
    std::vector<int> predict_weather;
    double accuracy;

    Viterbi();
    void parse(char* filename);
    void solve();
    void outputFile(char* filename);
};