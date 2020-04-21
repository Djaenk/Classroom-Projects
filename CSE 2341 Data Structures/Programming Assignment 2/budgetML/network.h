#ifndef NETWORK
#define NETWORK

#include "matrix.h"
#include "../DSlib/DSVector.h"
#include <random>
#include <cmath>

class Net{
	private:
		int input_count;
		int output_count;
		int hidden_layers; 	//The number of hidden layers can vary based on construction,
							//but every hidden layer has the same number of neurons as the input layer.
							//All layers are fully connected to the next layer.
		double eta;
		double alpha;
		DSVector<Matrix> weights;
		DSVector<Matrix> weight_deltas;
		DSVector<Matrix> values;
		DSVector<Matrix> gradients;
		double rms_error;

		std::default_random_engine rng;
		std::uniform_real_distribution<double> rand_dbl;

	public:
		Net(const int, const int, const int, const double, const double);
		void randomize_weights(const double);
		void set_weight_deltas(const double);
		
		void feed_input();
		void feed_forward(const int);
		static double activate(const double);
		static double activation_derivative(const double);
		void back_propagate(DSVector<double>);
		void train(Matrix&, Matrix&);

		DSVector<Matrix> get_weights()	{return weights;}
		DSVector<Matrix> get_values()	{return values;}
		double get_error()				{return rms_error;}
};

Net::Net(const int input_count, const int hidden_layers, const int output_count, const double learning_rate, const double momentum){
	this->input_count = input_count;
	this->output_count = output_count;
	this->hidden_layers = hidden_layers;
	eta = learning_rate;
	alpha = momentum;
	values.push_back(Matrix(input_count + 1, 1));
	gradients.push_back(Matrix(input_count, 1)); //the gradients of the input layer will never be used,
												//but this is still pushed into the vector to keep the
												//number of elements consistent with the values vector.
	for(int i = 0; i < hidden_layers; i++){ //generate the matrix of weights for hidden layers, if any
											//all layers except the output layer have a bias neuron
		weights.push_back(Matrix(input_count + 1, input_count));
		weight_deltas.push_back(Matrix(input_count + 1, input_count));
		//any hidden layers have the same number of neurons as the previous layer,
		//which has the same number of neurons as its previous layer
		values.push_back(Matrix(input_count + 1, 1));
		gradients.push_back(Matrix(input_count, 1));
	}
	weights.push_back(Matrix(input_count + 1, output_count));
	weight_deltas.push_back(Matrix(input_count + 1, output_count));
	//final matrix of weights for connections feeding to the output layer
	values.push_back(Matrix(output_count, 1));
	gradients.push_back(Matrix(output_count, 1));
	//set bias neuron values to 1.0
	for(int i = 0; i <= hidden_layers; i++){
		values[i][input_count][0] = 1.0;
	}
}

void Net::randomize_weights(const double max_weight){
	rng.seed(time(nullptr));
	rand_dbl = std::uniform_real_distribution<double>(0, max_weight);
	for(int i = 0; i <= hidden_layers; i++){
		for(int j = 0; j < input_count; j++){
			for(int k = 0; k < input_count; k++){
				weights[i][j][k] = rand_dbl(rng);
			}
		}
	}
}

void Net::set_weight_deltas(const double weight_delta){
	for(int i = 0; i < weight_deltas.len(); i++){
		for(int j = 0; j < weight_deltas[i].row_count(); j++){
			for(int k = 0; k < weight_deltas[i].col_count(); k++){
				weights[i][j][k] = weight_delta;
			}
		}
	}
}

void Net::feed_forward(DSVector<double> inputs){
	for(int j = 0; j < input_count; j++){ //update values of input layer
		values[0][j][0] = inputs[j];
	}
	//feed inputs through the hidden layer weights
	for(int i = 0; i < hidden_layers; i++){
		DSVector<double> outputs = DSVector<double>(input_count);
		for(int k = 0; k < input_count; k++){
			double sum = 0.0;
			for(int j = 0; j < input_count + 1; j++){
				sum += inputs[j] * weights[i][j][k];
			}
			sum += weights[i][input_count + 1][k]; //adds weight of bias neuron, which is independent of input
			outputs[k] = activate(sum);
		}
		inputs = outputs; //prepares to feed output into next layer

		for(int j = 0; j < input_count; j++){ //updates values of current layer neurons
			values[i][j][0] = inputs[j];
		}
	}
	//feeds output of hidden layer(s) to output weights
	DSVector<double> outputs = DSVector<double>(output_count);
	for(int k = 0; k < output_count; k++){
		double sum = 0.0;
		for(int j = 0; j < input_count + 1; j++){
			sum += inputs[j] * weights.back()[j][k];
		}
		sum += weights.back()[input_count + 1][k]; //ditto about bias neuron
	}
	inputs = outputs; //returns the network output to the procided vector
	for(int j = 0; j < output_count; j++){ //updates values of output layer neurons
		values.back()[j][0] = inputs[j];
	}
}

double Net::activate(const double value){
	return (tanh(value) + 1.0) / 2.0;
}

double Net::activation_derivative(const double value){
	return (1.0 - value * value) / 2.0;
}

void Net::back_propagate(DSVector<double> target){
	rms_error = 0.0;
	for(int i = 0; i < output_count; i++){
		rms_error += (target[i] - values.back()[i][0]) * (target[i] - values.back()[i][0]);
	}
	rms_error /= output_count;
	rms_error = sqrt(rms_error);

	for(int i = hidden_layers + 1; i > 0; i--){ //iterates from output layer to input layer
		if(i == hidden_layers + 1){ //if current iteration is output layer(first iteration)
			for(int k = 0; k < output_count; k++){
				//generates gradient based on target output
				gradients[i][k][0] = (target[k] - values.back()[k][0]) * activation_derivative(values.back()[k][0]);
				//updates input weights using new gradient and values of previous layer
				for(int j = 0; j < input_count; j++){
					double weight_change = (eta * values[i - 1][j][0] * gradients[i][k][0]) + (alpha * weight_deltas[i - 1][j][k]);
					weights[i - 1][j][k] += weight_change;
					weight_deltas[i - 1][j][k] = weight_change;
				}
			}
		}
		else{
			for(int k = 0; k < input_count; k++){
				//generates gradient based on gradients of next layer
				double sum = 0.0;
				for(int l = 0; l < gradients[i + 1].row_count(); l++){
					sum += weights[i][k][l] * gradients[i + 1][l][0];
				}
				gradients[i][k][0] = sum * activation_derivative(values[i][k][0]);
				//updates input weights using new gradient and values of previous layer
				for(int j = 0; j < input_count; j++){
					double weight_change = (eta * values[i - 1][j][0] * gradients[i][k][0]) + (alpha * weight_deltas[i - 1][j][k]);
					weights[i - 1][j][k] += weight_change;
					weight_deltas[i - 1][j][k] = weight_change;
				}
			}
		}
	}
}

void Net::train(Matrix& input_set, Matrix& target_set){
	for(int i = 0; i < input_set.row_count(); i++){
		DSVector<double> input = input_set.get_row_vector(i);
		feed_forward(input);
		DSVector<double> target = target_set.get_row_vector(i);
		back_propagate(target);
	}
}

#endif