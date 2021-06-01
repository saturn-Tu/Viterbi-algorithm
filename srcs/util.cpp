#include "util.h"
using namespace std;

Viterbi::Viterbi() {
    // initial weather_trans_matrix
    weather_trans_matrix[SUNNY][SUNNY] = log(0.8);
    weather_trans_matrix[SUNNY][FOGGY] = log(0.15);
    weather_trans_matrix[SUNNY][RAINY] = log(0.05);
    weather_trans_matrix[FOGGY][SUNNY] = log(0.2);
    weather_trans_matrix[FOGGY][FOGGY] = log(0.5);
    weather_trans_matrix[FOGGY][RAINY] = log(0.3);
    weather_trans_matrix[RAINY][SUNNY] = log(0.2);
    weather_trans_matrix[RAINY][FOGGY] = log(0.2);
    weather_trans_matrix[RAINY][RAINY] = log(0.6);
    // initial emission_matrix
    emission_matrix[SUNNY][0] = log(0.9);
    emission_matrix[SUNNY][1] = log(0.1);
    emission_matrix[FOGGY][0] = log(0.7);
    emission_matrix[FOGGY][1] = log(0.3);
    emission_matrix[RAINY][0] = log(0.2);
    emission_matrix[RAINY][1] = log(0.8);
    // initial init_weather_p
    init_weather_p[SUNNY] = log(0.5);
    init_weather_p[FOGGY] = log(0.25);
    init_weather_p[RAINY] = log(0.25);
}

void Viterbi::parse(char* filename) {
    ifstream input_file;
    input_file.open(filename);
    input_file >> predict_days;
    observed_wearing.resize(predict_days);
    ground_truth.resize(predict_days);
    back_record.resize(predict_days);
    delta.resize(predict_days);
    for(int n=0; n<predict_days; n++) {
        delta[n].resize(3);
        back_record[n].resize(3);
    }
    predict_weather.resize(predict_days);
    string line;
    // parse useless end line
    getline( input_file, line );
    for(int n=0; n<predict_days; n++) {
        getline( input_file, line );
        int pos = line.find(',');
        string weather = line.substr(0, pos);
        string coat = line.substr(pos+1);
        if(weather == "sunny")
            ground_truth[n] = SUNNY;
        else if (weather == "foggy")
            ground_truth[n] = FOGGY;
        else if (weather == "rainy")
            ground_truth[n] = RAINY;
        else
            assert(false);
        if(coat == "no")
            observed_wearing[n] = 0;
        else if(coat == "yes")
            observed_wearing[n] = 1;
        else
            assert(false);
    }
    input_file.close();
}

void Viterbi::solve() {
    bool day0_wear = observed_wearing[0];
    delta[0][SUNNY] = init_weather_p[SUNNY]+emission_matrix[SUNNY][day0_wear];
    delta[0][FOGGY] = init_weather_p[FOGGY]+emission_matrix[FOGGY][day0_wear];
    delta[0][RAINY] = init_weather_p[RAINY]+emission_matrix[RAINY][day0_wear];
    for(int n=1; n<predict_days; n++) {
        bool dayn_wear = observed_wearing[n];
        for(int w=0; w<3; w++) {
            double max_p = INT32_MIN, max_idx = 0;
            for(int pre_w=0; pre_w<3; pre_w++) {
                double previous_p = delta[n-1][pre_w]+weather_trans_matrix[pre_w][w];
                if(max_p < previous_p) {
                    max_p = previous_p;
                    max_idx = pre_w;
                }
            }
            delta[n][w] = max_p+emission_matrix[w][dayn_wear];
            back_record[n][w] = max_idx;
        }
    }
    double max_p = INT32_MIN, max_idx = 0;
    for(int w=0; w<3; w++) {
        if(max_p < delta.back()[w]) {
            max_p = delta.back()[w];
            max_idx = w;
        }
    }
    predict_weather.back() = max_idx;
    for(int n=delta.size()-2; n>=0; n--) {
        int next_weather = predict_weather[n+1];
        predict_weather[n] = back_record[n+1][next_weather];
    }
    int correct_count = 0;
    for(int n=0; n<predict_days; n++) {
        if(predict_weather[n] == ground_truth[n])
            correct_count++;
    }
    accuracy = (double)correct_count/predict_days;
}

void Viterbi::outputFile(char* filename) {
    ofstream output_file;
    output_file.open(filename);
    output_file << accuracy << endl;
    for(auto& weather : predict_weather) {
        if(weather == SUNNY)
            output_file << "sunny\n";
        else if(weather == FOGGY)
            output_file << "foggy\n";
        else if(weather == RAINY)
            output_file << "rainy\n";
    }
    output_file.close();
}