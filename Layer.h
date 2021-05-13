
// Created by blackstone on 23.04.21.
//
#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H
#include <vector>
class Layer {
public:
    Layer();
    Layer(int num_of_neuron,int num_of_inp);
    Layer(int num_of_neuron);
    Layer(std::vector<float>weight,std::vector<float>layer_neurons);
    void set_weights(std::vector<std::vector<float>>&new_weights);
    void set_layer(std::vector<float>layer_node);
    void set_layer_id(int id);
    void set_input_values(std::vector<float>&input_values);
    void set_error_values(std::vector<float>&errors);
    std::vector<double>get_error_values();
    std::vector<float>&get_layer_node();
    std::vector<std::vector<float>>&get_weights();
private:
    std::vector<float>Layer_node;
    std::vector<float>Input_values;
    std::vector<std::vector<float>>_weights;
    std::vector<double>error_values;
    int layer_id;
    int neuron_num;
};
#endif //NEURALNETWORK_LAYER_H
