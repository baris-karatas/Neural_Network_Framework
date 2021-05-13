#include <iostream>
#include "Network.h"
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
struct datasset{
    std::vector<float>inputs;
    std::vector<float>target;
};
void print_img(std::vector<float>img,std::vector<float>target){
    for(size_t i=0;i<target.size();i++){
        std::cout<<target.at(i)<<"\t";
    }
    std::cout<<"\n\n";
    for(size_t i=0;i<img.size();i++){

        std::cout<<img.at(i)<<"\t";
        if(i%28==0&&i!=0){
            std::cout<<std::endl;
        }
    }

}
std::vector<float> corrected_img(Mat &img){
    std::vector<float>inputs;
    std::vector<int>prints;
    float tmp;
    for(size_t i=0;i<img.rows;i++){
        for(size_t j=0;j<img.cols;j++){
            tmp=(float)img.at<uchar>(i,j)/255;
            if(tmp==1){
                inputs.push_back(0.999);
            }else if(tmp==0){
                inputs.push_back(0.001);
            }else{
                inputs.push_back(tmp);
            }
        }
    }
    /*
    for(size_t i=0;i<prints.size();i++){

        std::cout<<prints.at(i)<<"\t";
        if(i%28==0&&i!=0){
            std::cout<<std::endl;
        }
    }
*/

    return inputs;
}
void test(Network &ark){
    std::vector<float>inputs;
    char src_add[200];
    float counter=0;
    int size=0;
    std::vector<String>filename;
    for(size_t fold=0;fold<10;fold++){
        sprintf(src_add,"/home/blackstone/Desktop/NeuralNetwork/cmake-build-debug/testing/%d/",fold);
        glob(src_add,filename);
        for(size_t i=0;i< filename.size();i++){
            Mat src= imread(filename.at(i),IMREAD_GRAYSCALE);
            std::vector<float>inputss= corrected_img(src);
            ark.get_inputs_con(inputss);
            ark.feed_forwad();
            size++;
            if(fold==ark.out_show()){
                counter++;
            }
        }
    }
    counter=((float)counter/size)*100;
    std::cout<<"the test prediction is : "<<counter<<std::endl;

}
struct data_xor{
    std::vector<float>input;
    std::vector<float>output;
};

int main() {
    std::cout << "Hello, welcome to my neural network" << std::endl;

    std::vector<float>inputs(784,0.0);
    std::vector<float>inputsss{0.01,0.99};
    std::vector<data_xor>input;

    char src_add[80];
    std::string addres="weights.txt";
    /*
    data_xor tmp;
    tmp.input.push_back(0.01);
    tmp.input.push_back(0.99);
    tmp.output.push_back(0.99);
    input.push_back(tmp);
    tmp.input.at(0)=0.01;
    tmp.input.at(1)=0.99;
    tmp.output.at(0)=0.99;
    input.push_back(tmp);
    tmp.input.at(0)=0.99;
    tmp.input.at(1)=0.99;
    tmp.output.at(0)=0.00;
    input.push_back(tmp);
    tmp.input.at(0)=0.01;
    tmp.input.at(1)=0.01;
    tmp.output.at(0)=0.01;
    input.push_back(tmp);

     */
/*
    for(size_t i=0;i<10000000;i++){
        std::random_shuffle(input.begin(),input.end());
        for(size_t j=0;j<input.size();j++){
            ark.get_inputs_con(input.at(j).input);
            ark.get_target(input.at(j).output);
            ark.feed_forwad();
            ark.back_propagation();
            ark.error_sum();
        }

    }


*/
    Network ark(inputs,2 ,50,10);
    ark.load_weigts(addres);
    //test(ark);
    //test(ark);
    std::vector<float>target0{0.999,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001};
    std::vector<float>target1{0.001,0.999,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001};
    std::vector<float>target2{0.001,0.001,0.999,0.001,0.001,0.001,0.001,0.001,0.001,0.001};
    std::vector<float>target3{0.001,0.001,0.001,0.999,0.001,0.001,0.001,0.001,0.001,0.001};
    std::vector<float>target4{0.001,0.001,0.001,0.001,0.999,0.001,0.001,0.001,0.001,0.001};
    std::vector<float>target5{0.001,0.001,0.001,0.001,0.001,0.999,0.001,0.001,0.001,0.001};
    std::vector<float>target6{0.001,0.001,0.001,0.001,0.001,0.001,0.999,0.001,0.001,0.001};
    std::vector<float>target7{0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.999,0.001,0.001};
    std::vector<float>target8{0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.999,0.001};
    std::vector<float>target9{0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.999};
    std::vector<std::pair<std::vector<float>,std::vector<float>>>list;
    std::vector<struct datasset>data;
    for(size_t fold=0;fold<10;fold++){
        std::vector<String>filename;
        sprintf(src_add,"/home/blackstone/Desktop/NeuralNetwork/cmake-build-debug/training/%d/",fold);
        glob(src_add,filename);
        std::vector<float>target;
        switch (fold) {
            case 0:target=target0;
                break;
            case 1:target=target1;
                break;
            case 2:target=target2;
                break;
            case 3:target=target3;
                break;
            case 4:target=target4;
                break;
            case 5:target=target5;
                break;
            case 6:target=target6;
                break;
            case 7:target=target7;
                break;
            case 8:target=target8;
                break;
            case 9:target=target9;
                break;
        }
        for(size_t i=0;i<filename.size();i++){
            Mat src= imread(filename.at(i),IMREAD_GRAYSCALE);
            std::vector<float>inputss= corrected_img(src);
            list.push_back(std::make_pair(target,inputss));
            datasset tmp;
            tmp.inputs=inputss;
            tmp.target=target;
            data.push_back(tmp);
        }
    }
    std::random_shuffle(list.begin(),list.end());
    std::random_shuffle(data.begin(),data.end());
    int counter=0;
    for(size_t j=0;j<10;j++){
        for(size_t i=0;i<data.size();i++){
            ark.get_inputs_con(data.at(i).inputs);
            ark.get_target(data.at(i).target);
            ark.feed_forwad();
           // ark.back_propagation();
            if(i%5000==0&i!=0){
                ark.write_nodes_weights();
                ark.error_sum();
                //ark.error_sum();
            }
        }

        test(ark);
        ark.write_nodes_weights();
    }
    return 0;
}
//to do list
//make program to compatible with importing nodes and weights
//make program owrrite weights and nodes
//get output num of neurons

