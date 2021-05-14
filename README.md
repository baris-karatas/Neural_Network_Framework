# Neural Network Framework
I tried to crete a neural network framework that user can create multi-layer neural network easly.

This framework currently has some features;
  * feed forward
  * Backpropagation
  * weight load-upload
 
 This framework eventually will have multiple network constructor to create various neural network types.
 
 Cosntructor:
 
  ![image](https://user-images.githubusercontent.com/33378290/118195393-d6905300-b453-11eb-9785-5e0c956dbc68.png)
  
  * First parameter gets input vector that will be used to create input layer of neural network.
  
  * Second parameter gets number of hidden layer to create multiple hidden layer in neural network.
  
  * Third parameter number of neurons in each single hidden layer so we can create multiple hidden-layer with various neurons.  
  
  * Forth parameter gets number of neurons to create output layer
  
# Results:
 To test neural network I did create some neural networks with diffrent hidden layers and neurons.
  
  * 786 X 25 X 25 X 10 = this networks has 786 input nodes, and two hidden layers that each one has 25 neurons, 10 outpus.
    I trained the network with MIST dataset that contain handwritten numbers 
    
   ![5](https://user-images.githubusercontent.com/33378290/118197184-1c9ae600-b457-11eb-9a3b-9fbd80de8411.jpg)
   ![10](https://user-images.githubusercontent.com/33378290/118197265-418f5900-b457-11eb-8575-822cddfe50ba.jpg)
   ![38](https://user-images.githubusercontent.com/33378290/118197276-46eca380-b457-11eb-8360-9ac1f901d195.jpg)
   ![19](https://user-images.githubusercontent.com/33378290/118197294-4f44de80-b457-11eb-98a4-06ba175e6ba4.jpg)
   ![81](https://user-images.githubusercontent.com/33378290/118197302-553abf80-b457-11eb-938a-a903e894a7dd.jpg)
   
   like these handwritten numbers.
   
   ![2*25_neuralfinal](https://user-images.githubusercontent.com/33378290/118197675-13f6df80-b458-11eb-9cd4-b297d677b849.png)
   
    as in the picture after couple hour training we reach the around %94 accuracy in test folder.
  * 786 X 50 X 50 X 10 = this networks has 786 input nodes, and two hidden layers that each one has 50 neurons, 10 outpus.
  
  ![50*2](https://user-images.githubusercontent.com/33378290/118197966-abf4c900-b458-11eb-987a-fd788f0a9484.png)

  
   I reach around %96 percentage of accuracy in the test folder. it is very promising.
   
# Notes
I tried with different network sizes to see training speed and accuracy changing. We can create more sophisticated networks to reach higgest accuracy rate or we can decrease complication of network bu more we train our network with different data ce can reach higger accuracy rates.

When we increase complication of the network, meanwhile we increase parameters of networks which means we need more process and runtime.
I write my own matrix multiplication and other theories so the optimization of framework may not be the best one but I will try to make faster.  


# Todos

* This fremework runs on cpu but in the following days I will add Gpu support to speed up procces.

* Support to convolutional neural networks.
* Support to reinforcement neural networs.
* Support to language recocginiton.







