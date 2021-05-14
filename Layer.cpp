//
// Created by blackstone on 23.04.21.
//

#include "Layer.h"
#include <stdlib.h>
#include <ctime>

Layer::Layer(int num_of_neuron,int num_of_inp) {
    srand((unsigned) time(0));
    std::vector<std::vector<float>>weights(num_of_inp,std::vector<float>(num_of_neuron));
    std::vector<float>nodes(num_of_neuron);
    Layer::Layer_node=nodes;
    Layer::_weights=weights;
    this->neuron_num=num_of_neuron;
    for(size_t i=0;i<num_of_neuron;i++){
        Layer::Layer_node.at(i)=(float) rand() / RAND_MAX;
        Layer::error_values.push_back((float )rand() / RAND_MAX);
        Layer::Input_values.push_back((float )rand() / RAND_MAX);
    }
    for(size_t i=0;i<num_of_inp;i++){
        for(size_t j=0;j<num_of_neuron;j++){
            int tmp=rand();
            if(tmp%2==0){
                _weights.at(i).at(j)=((float) rand() / RAND_MAX)/2;
            }else{
                _weights.at(i).at(j)=((float) rand() / RAND_MAX)/2*-1;
            }
        }
    }
}
Layer::Layer(int num_of_neuron) {
    srand((unsigned) time(0));
    std::vector<std::vector<float>>weights(num_of_neuron,std::vector<float>(num_of_neuron));
    std::vector<float>nodes(num_of_neuron);
    Layer::Layer_node=nodes;
    Layer::_weights=weights;
    this->neuron_num=num_of_neuron;
    for(size_t i=0;i<num_of_neuron;i++){
        Layer::Layer_node.at(i)=(float) rand() / RAND_MAX;
        Layer::error_values.push_back((float )rand() / RAND_MAX);
        Layer::Input_values.push_back((float )rand() / RAND_MAX);
        for(size_t j=0;j<num_of_neuron;j++){
            int tmp=rand();
            if(tmp%2==0){
                _weights.at(i).at(j)=((float )rand() / RAND_MAX)/2;
            }else{
                _weights.at(i).at(j)=((float )rand() / RAND_MAX)/2*-1;
            }

        }
    }
}
void Layer::set_layer(std::vector<float> layer_node) {
    for(size_t i=0;i<layer_node.size();i++){
        Layer::Layer_node.at(i)=layer_node.at(i);
    }
}
void Layer::set_weights(std::vector<std::vector<float>>&new_weights) {
    for(size_t i=0;i<new_weights.size();i++){
        for(size_t j=0;j<new_weights.at(0).size();j++){
            Layer::_weights.at(i).at(j)=new_weights.at(i).at(j);
        }
    }
}
void Layer::set_input_values(std::vector<float>&input_values){
    for(size_t i=0;i<input_values.size();i++){
        Input_values.at(i)=input_values.at(i);
    }
}
std::vector<float>& Layer::get_layer_node() {
    return Layer::Layer_node;
}
void Layer::set_error_values(std::vector<float> &errors) {
    for(size_t i=0;i<errors.size();i++){
        error_values.at(i)=errors.at(i);
    }
}
std::vector<double>Layer::get_error_values() {
    return error_values;
}
std::vector<std::vector<float>>&Layer::get_weights(){
    return Layer::_weights;
}
void Layer::set_layer_id(int id) {
    layer_id=id;
}