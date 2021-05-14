//
// Created by blackstone on 23.04.21.
//

#include "Network.h"
#include <iterator>
Network::Network(const int layer_num,const int num_of_neuron, const int output_num):Output(num_of_neuron,output_num){
    this->layer_num=layer_num;
    this->hidden_node_num=num_of_neuron;
    this->output_node_num=output_num;

    Layer layer(num_of_neuron,_inputs.size());

    hidden_layer.push_back(layer);


    for(size_t i=0;i<layer_num-1;i++){
        Layer layer(num_of_neuron);
        layer.set_layer_id(i+1);
        hidden_layer.push_back(layer);
    }
}
Network::Network(std::vector<float>&inputs,int layer_num,int node_numi,int output_node_num):Output(node_numi,output_node_num){
    this->layer_num=layer_num;
    this->hidden_node_num=node_numi;
    this->output_node_num=output_node_num;

    Network::get_inputs(inputs);
    Layer layer(node_numi,_inputs.size());
    hidden_layer.push_back(layer);

    for(size_t i=1;i<layer_num;i++){
        Layer layer(node_numi);
        layer.set_layer_id(i);
        hidden_layer.push_back(layer);
    }
}
Network::Network(int layer_num, int num_of_neuron):Output(num_of_neuron,num_of_neuron){
    this->layer_num=layer_num;
    for(size_t i=0;i<layer_num;i++){
         Layer layer(num_of_neuron);
         layer.set_layer_id(i);
        hidden_layer.push_back(layer);
    }
}
std::vector<float> Network::Activation_fun_sigmo(std::vector<float>layers){
    for(size_t i=0;i<layers.size();i++){
        layers.at(i)=1/(1+ exp((-1)*layers.at(i)));
    }
    return layers;
}
void Network::get_inputs(std::vector<float> &input) {
    _inputs=input;
}
void Network::get_inputs_con(std::vector<float> &input) {
    for(size_t i=0;i<input.size();i++){
        _inputs.at(i)=input.at(i);
    }
}
std::vector<float>Network::multiply_mat(  std::vector<float>&matris1,std::vector<std::vector<float>>&matris2){
 std::vector<float>multi(matris2.at(0).size(),0.0);

 for(size_t i=0;i<matris2.at(0).size();i++){
         for(size_t k=0;k<matris2.size();k++){
             multi.at(i)+=matris1.at(k)*matris2.at(k).at(i);
         }
 }

    return multi;
}
void Network::feed_forwad() {
    std::vector<std::vector<float>>weights;
    std::vector<float>nodes;

    weights=hidden_layer.at(0).get_weights();
    nodes=multiply_mat(_inputs,weights);
    hidden_layer.at(0).set_input_values(nodes);
    hidden_layer.at(0).set_layer(Activation_fun_sigmo(nodes));

    for(size_t i=0;i<layer_num-1;i++){
        std::vector<float>nodes=multiply_mat(hidden_layer.at(i).get_layer_node(),hidden_layer.at(i+1).get_weights());
        hidden_layer.at(i+1).set_layer(Activation_fun_sigmo(nodes));

    }
    std::vector<float>outputs=multiply_mat(hidden_layer.at(layer_num-1).get_layer_node(),Output::get_output_weights());
    Output::set_output(Activation_fun_sigmo(outputs));
}
std::vector<float> Network::find_errors_hidden(std::vector<std::vector<float>>&weights,std::vector<double>&error_l,std::vector<double>&error_r,std::vector<float>&output_l,std::vector<float>&output_r){

    const int right_node_num=error_r.size();
    const int left_node_num=error_l.size();

    std::vector<float>hidden_errors(left_node_num,0.0);
    std::vector<std::vector<float>>weigths_ds(left_node_num,std::vector<float>(right_node_num,0));
    for(size_t i=0;i<right_node_num;i++){
        for(size_t j=0;j<left_node_num;j++){
            weigths_ds.at(j).at(i)=error_r.at(i)*(output_r.at(i)*(1-output_r.at(i)))*weights.at(j).at(i);
            weights.at(j).at(i)+=output_r.at(i)*(1-output_r.at(i))*error_r.at(i)*output_l.at(j)*0.5*(-1);//check error_r point
        }
    }
    for(size_t i=0;i<left_node_num;i++){
        for(size_t j=0;j<right_node_num;j++){
            hidden_errors.at(i)+=weigths_ds.at(i).at(j);
        }
    }
    return hidden_errors;
}
std::vector<float> Network::find_errors_out(std::vector<std::vector<float>>&weights,std::vector<double>&error_l,std::vector<double>&error_r,std::vector<float>&output_l,std::vector<float>&output_r){

    int right_node_num=error_r.size();
    int left_node_num=error_l.size();

    std::vector<float>hidden_errors(left_node_num,0.0);
    std::vector<std::vector<float>>weigths_ds(left_node_num,std::vector<float>(right_node_num,0));
    for(size_t i=0;i<right_node_num;i++){
        for(size_t j=0;j<left_node_num;j++){
            weigths_ds.at(j).at(i)=error_r.at(i)*(output_l.at(j)*(1-output_l.at(j)))*weights.at(j).at(i);
            weights.at(j).at(i)+=output_r.at(i)*(1-output_r.at(i))*error_r.at(i)*output_l.at(j)*0.2*(-1);//check error_r point
        }
    }
    for(size_t i=0;i<left_node_num;i++){
        for(size_t j=0;j<right_node_num;j++){
            hidden_errors.at(i)+=weigths_ds.at(i).at(j);
        }
    }
    return hidden_errors;
}

void Network::back_propagation() {
    Output::find_output_errors();
    //Output::error_sum();
    std::vector<double>error_l=hidden_layer.at(hidden_layer.size()-1).get_error_values();
    std::vector<double>error_r=Output::get_error_values();
    std::vector<float>outpur_l=hidden_layer.at(hidden_layer.size()-1).get_layer_node();
    std::vector<float>outpt_r=Output::get_output_val();
    std::vector<std::vector<float>>weigths=Output::get_output_weights();
    std::vector<float>errors=find_errors_hidden(weigths,error_l,error_r,outpur_l,outpt_r);


    hidden_layer.at(hidden_layer.size()-1).set_error_values(errors);
    Output::set_weights(weigths);


    for(size_t i=hidden_layer.size()-1;i>0;i--){
        std::vector<double>error_l=hidden_layer.at(i-1).get_error_values();
        std::vector<double>error_r=hidden_layer.at(i).get_error_values();
        std::vector<float>output_r=hidden_layer.at(i).get_layer_node();
        std::vector<std::vector<float>>weigths_=hidden_layer.at(i).get_weights();
        std::vector<float>outpur_l=hidden_layer.at(i-1).get_layer_node();
        std::vector<float>errors=find_errors_hidden(weigths_,error_l,error_r,outpur_l,output_r);


        hidden_layer.at(i-1).set_error_values(errors);
        hidden_layer.at(i).set_weights(weigths_);
    }
    std::vector<double>err_l(_inputs.size(),0.0);
    std::vector<float>output_r=hidden_layer.at(0).get_layer_node();
    std::vector<double>err_r=hidden_layer.at(0).get_error_values();
    std::vector<std::vector<float>>weig=hidden_layer.at(0).get_weights();
    std::vector<float>out_l=_inputs;
    std::vector<float>err=find_errors_hidden(weig,err_l,err_r,out_l,output_r);
    hidden_layer.at(0).set_weights(weig);
}
void Network::write_nodes_weights() {
    std::ofstream weigts("_weights.txt");
    if(!weigts)
        std::cout<<"Error cannot create weights file !!!\n";
    weigts<<"Inputs_node_num= "<<_inputs.size()<<"\n";
    weigts<<"hidden_layer_num= "<<hidden_layer.size()<<"\n";
    weigts<<"hidden_node_num= "<<hidden_layer.at(0).get_layer_node().size()<<"\n";
    weigts<<"output_node_num= "<<Output::get_output_val().size()<<"\n";
    for(size_t i=0;i<hidden_layer.size();i++){//  !importat only works for eaqual inputs and hidden leyer of nodes
        std::ostream_iterator<float>output_iterator(weigts," ");
        for(size_t j=0;j<hidden_layer.at(i).get_weights().size();j++){
            std::vector<float>weights=hidden_layer.at(i).get_weights().at(j);
            std::copy(weights.begin(),weights.end(),output_iterator);
        }
    }
    std::vector<std::vector<float>>weights=Output::get_output_weights();
    for(size_t i=0;i<hidden_node_num;i++){
        for(size_t j=0;j<output_node_num;j++){
          weigts<<weights.at(i).at(j)<<" ";
        }
    }

    weigts.close();
}
void Network::write_nodes_weights(char *name) {
    std::ofstream weigts(name);
    if(!weigts)
        std::cout<<"Error cannot create weights file !!!\n";
    weigts<<"Inputs_node_num= "<<_inputs.size()<<"\n";
    weigts<<"hidden_layer_num= "<<hidden_layer.size()<<"\n";
    weigts<<"hidden_node_num= "<<hidden_layer.at(0).get_layer_node().size()<<"\n";
    weigts<<"output_node_num= "<<Output::get_output_val().size()<<"\n";
    for(size_t i=0;i<hidden_layer.size();i++){//  !importat only works for eaqual inputs and hidden leyer of nodes
        std::ostream_iterator<float>output_iterator(weigts," ");
        for(size_t j=0;j<hidden_layer.at(i).get_weights().size();j++){
            std::vector<float>weights=hidden_layer.at(i).get_weights().at(j);
            std::copy(weights.begin(),weights.end(),output_iterator);
        }
    }
    std::vector<std::vector<float>>weights=Output::get_output_weights();
    for(size_t i=0;i<hidden_node_num;i++){
        for(size_t j=0;j<output_node_num;j++){
            weigts<<weights.at(i).at(j)<<" ";
        }
    }

    weigts.close();
}
void Network::load_weigts(std::string &address) {
    std::ifstream weights("/home/blackstone/Desktop/NeuralNetwork/cmake-build-debug-coverage/_weights.txt");//this directory can be chaged
    std::vector<float>_weights;
    int input_nodenum;
    int hidden_num;
    int output_node_num;
    int hidden_node_num;
    float temp;
    char type[40];
    if(!weights)
        std::cout<<"Error with load weights;";
    else {
        weights >> type >> input_nodenum;
        weights >> type >> hidden_num;
        weights >> type >> hidden_node_num;
        weights >> type >> output_node_num;
        std::vector<std::vector<float>> input_wei(input_nodenum, std::vector<float>(hidden_node_num, 0.0));
        for (size_t i = 0; i < input_nodenum; i++) {
            for (size_t j = 0; j < hidden_node_num; j++) {
                weights >> temp;
                input_wei.at(i).at(j) = temp;
            }
        }
        hidden_layer.at(0).set_weights(input_wei);
        for (size_t i = 1; i < hidden_num; i++) {
            std::vector<std::vector<float>> hidden_weigts(hidden_node_num, std::vector<float>(hidden_node_num, 0.0));
            for (size_t j = 0; j < hidden_node_num; j++) {
                for (size_t k = 0; k < hidden_node_num; k++) {
                    weights >> temp;
                    hidden_weigts.at(j).at(k) = temp;
                }
            }
            hidden_layer.at(i).set_weights(hidden_weigts);
        }
        std::vector<std::vector<float>> output_weights(hidden_node_num, std::vector<float>(output_node_num, 0.0));
        for (size_t i = 0; i < hidden_node_num; i++) {
            for (size_t j = 0; j < output_node_num; j++) {
                weights >> temp;
                output_weights.at(i).at(j) = temp;
            }
        }
        Output::set_weights(output_weights);
        weights.close();
    }
}