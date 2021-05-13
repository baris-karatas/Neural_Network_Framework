//
// Created by blackstone on 23.04.21.
//

#ifndef NEURALNETWORK_OUTPUT_H
#define NEURALNETWORK_OUTPUT_H
#include <vector>
#include <iostream>
class Output {
public:
    Output();
    Output(int node_numi,int output_node_num);
    void set_weights(std::vector<std::vector<float>>&new_weights);
    void set_output(std::vector<float>outputs);
    void find_output_errors();
    void set_input_values(std::vector<float>&inputs);
    void get_target(std::vector<float>&target);
    std::vector<std::vector<float>>&get_output_weights();
    std::vector <double>get_error_values();
    void error_sum();
    std::vector<float>get_output_val();
    int out_show();


private:
    std::vector <float>output_values;
    std::vector<float>input_val;
    std::vector<std::vector<float>>_weights;
    std::vector<float>_target;
    std::vector <double>error_values;
};

#endif //NEURALNETWORK_OUTPUT_H
