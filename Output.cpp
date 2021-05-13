//
// Created by blackstone on 23.04.21.
//
#include <stdlib.h>
#include <ctime>
#include "Output.h"
#include <bits/stdc++.h>
Output::Output(int node_num,int output_node_num) {
    std::vector<std::vector<float>>weight(node_num,std::vector<float>(output_node_num,0.0));
    srand((unsigned) time(0));
    for(size_t i=0;i<output_node_num;i++){
        for(size_t j=0;j<node_num;j++){
            int tmp=rand();

            if(tmp%2==0){
                weight.at(j).at(i)=((float) rand() / RAND_MAX)/2;
                //weight.at(j).at(i)=1;
            }else{
                weight.at(j).at(i)=((float) rand() / RAND_MAX)/2*-1;
                //weight.at(j).at(i)=-1;
            }
            //weight.at(j).at(i)=(float) rand() / RAND_MAX;
        }
        output_values.push_back((float)rand()/RAND_MAX);
        _target.push_back((float)rand()/RAND_MAX);
        error_values.push_back((float)rand()/RAND_MAX);
        input_val.push_back((float)rand()/RAND_MAX);
    }
    _weights=weight;
}
void Output::set_output(std::vector<float> outputs) {
    for(size_t i=0;i<outputs.size();i++)
        this->output_values.at(i)=outputs.at(i);
}
std::vector<std::vector<float>>&Output::get_output_weights() {
    return _weights;
}
std::vector<double>Output::get_error_values() {
    return error_values;
}
void Output::set_input_values(std::vector<float> &inputs) {
    for(size_t i=0;i<inputs.size();i++){
        Output::input_val.at(i)=inputs.at(i);
    }
}
void Output::set_weights(std::vector<std::vector<float>>&new_weights){
    for(size_t i=0;i<new_weights.size();i++){
        for(size_t j=0;j<new_weights.at(0).size();j++){
            Output::_weights.at(i).at(j)=new_weights.at(i).at(j);
        }
    }
}
std::vector<float>Output::get_output_val() {
    return Output::output_values;
}
void Output::find_output_errors(){
    for(size_t i=0;i<error_values.size();i++){
        error_values.at(i)=-(_target.at(i)-output_values.at(i));
    }
}
void Output::get_target(std::vector<float> &target){
    for(size_t i=0;i<target.size();i++){
        _target.at(i)=target.at(i);
    }
}
void Output::error_sum() {
    double sum=0.0000000001;
    for(size_t i=0;i<Output::error_values.size();i++){
        sum+=(_target.at(i)-output_values.at(i))*(_target.at(i)-output_values.at(i));
    }
    std::cout<< "Total error : "<<sum<<std::endl;
}
int Output::out_show() {
    float max;
    int max_ind;
    max=Output::output_values.at(0);
    max_ind=0;
    for(size_t i=0;i<output_values.size();i++){
        if(max<output_values.at(i)){
            max_ind=i;
            max=output_values.at(i);
        }
    }
    return max_ind;

}
