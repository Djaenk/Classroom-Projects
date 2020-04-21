#ifndef REGRESSION
#define REGRESSION

#include <vector>
#include <cmath>

void least_squares_regression(std::vector<long double>, std::vector<long double>, long double&, long double&, long double&);
int fit_curve(std::vector<long double>, std::vector<long double>);
long double mean(std::vector<long double>);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Performing a linear regression on the runtime data and evaluating the
//error of a given regression is the core of the guesser's logic.
//This implementation is based on how a linear regression is typically solved mathematically:
//https://towardsdatascience.com/linear-regression-derivation-d362ea3884c2
//http://seismo.berkeley.edu/~kirchner/eps_120/Toolkits/Toolkit_10.pdf
void least_squares_regression(std::vector<long double> x, std::vector<long double> y, long double& slope, long double& intercept, long double& MSPE){
    MSPE = 0.0;
    long double covariance_xy = 0.0;
    long double variance_x = 0.0;
    long double mean_x = mean(x);
    long double mean_y = mean(y);

    for(int i = 0; i < y.size(); i++){
        covariance_xy += x[i] * (y[i] - mean_y);
        variance_x += x[i] * (x[i] - mean_x);
    }
    slope = covariance_xy / variance_x;
    intercept = mean_y - slope * mean_x;

    for(int i = 0; i < y.size(); i++){
        MSPE += ((intercept + slope * x[i]) / y[i]) * ((intercept + slope * x[i]) / y[i]);
    }
    MSPE /= y.size();
}

//determines if passed data best fits a function of linear, linear logarithmic, or quadratic
//asymptotic behavior. Returns 1,2, or 3 repectively if so. Returns 0 if inconclusive
int fit_curve(std::vector<long double> x, std::vector<long double> y){
	long double a,b; //throwaway values to store slope and intercept of linear regression
	std::vector<long double> x_lin_adjusted, x_linlog_adjusted, x_quad_adjusted;
	long double error_lin, error_linlog, error_quad;

	for(int i = 0; i < 5; i++){
		y.erase(y.begin());
	}
	for(int i = 5; i < x.size(); i++){
		x_lin_adjusted.push_back(x[i]);
		x_linlog_adjusted.push_back(x[i] * log2(x[i]));
		x_quad_adjusted.push_back(x[i] * x[i]);
	}

	least_squares_regression(x_lin_adjusted, y, b, a, error_lin);
	least_squares_regression(x_linlog_adjusted, y, b, a, error_linlog);
	least_squares_regression(x_quad_adjusted, y, b, a, error_quad);

	if(error_lin <= error_linlog && error_lin <= error_quad){
		return 1;
	}
	else if(error_linlog < error_lin && error_linlog < error_quad){
		return 2;
	}
	else if(error_quad < error_lin && error_quad < error_linlog){
		return 3;
	}
	else{
		return 0;
	}
}

long double mean(std::vector<long double> values){
    long double mean = 0.0;
    for(int i = 0; i < values.size(); i++){
        mean += values[i];
    }
    mean /= values.size();
    return mean;
}
#endif
