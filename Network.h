//
// Created by blackstone on 23.04.21.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H
#include "Layer.h"
#include "Output.h"
#include <math.h>       /* exp */
#include <fstream>
#include <iostream>
class Network:public Output {
public:
    Network();
    Network(int layer_num,int num_of_neuron);
    Network(const int layer_num,const int num_of_neuron,const int output_num);//to create empty neural network;
    Network(std::vector<float>&inputs,int layer_num,int node_numi,int output_node_num);

    std::vector<float>multiply_mat( std::vector<float>&matris1, std::vector<std::vector<float>>&matris2);
    std::vector<float> find_errors_out(std::vector<std::vector<float>>&weights,std::vector<double>&error_l,std::vector<double>&error_r,std::vector<float>&output_l,std::vector<float>&output_r);
    std::vector<float> find_errors_hidden(std::vector<std::vector<float>>&weights,std::vector<double>&error_l,std::vector<double>&error_r,std::vector<float>&output_l,std::vector<float>&output_r);
    std::vector<float> Activation_fun_sigmo(std::vector<float>layers);

    std::vector<float> Activation_fun_step();
    void get_inputs(std::vector<float>&input);
    void get_inputs_con(std::vector<float>&input);
    void find_last_hidden_errors(); //Network()//to import already existed network;; get weightsden_errors();
    void write_nodes_weights();
    void write_nodes_weights(char *name);
    void find_hidden_errors();
    void back_propagation();
    void feed_forwad();
    void load_weigts(std::string &address);

private:
    std::vector<Layer>hidden_layer;
     int layer_num;
     int output_node_num;
     int hidden_node_num;
    std::vector<float>_inputs;

};


#endif //NEURALNETWORK_NETWORK_H
