#include <iostream>
#include <regex>
#include <string>
#include <cmath>
#include <limits>
#include <vector>
#include <stdexcept>
#include <cfloat>

enum input_indices
{
	X1_VALUE = 1,
	Y1_VALUE,
	X2_VALUE,
	Y2_VALUE,
	ROUNDING_PLACE
};

typedef enum
{
	NO_ERROR,
	DIV_BY_ZERO,
	INFINITY_REACHED,
	INVALID_COORD_INPUT,
	INVALID_ROUNDING_PLACE_INPUT

} error_code_t;

typedef struct 
{
	error_code_t x1_value_check = NO_ERROR;
	error_code_t y1_value_check = NO_ERROR;
	error_code_t x2_value_check = NO_ERROR;
	error_code_t y2_value_check = NO_ERROR;

} input_sanitizer_checks_t;


typedef struct 
{
	double x;
	double y;

} point_t;

typedef struct
{
	error_code_t error_code = NO_ERROR;
	double       value      = 0.0;

} result_t;


void print_error_code(error_code_t error_code)
{
	switch(error_code)
	{
		case NO_ERROR:
			std::cout<<"Input is good!\n";
			break;
		case DIV_BY_ZERO:
			std::cout<<"error: DIV_BY_ZERO\n";
			break;
		case INFINITY_REACHED:
			std::cout<<"error: INFINITY_REACHED\n";
			break;
		case INVALID_COORD_INPUT:
			std::cout<<"error: INVALID_COORD_INPUT\n";
			break;
		case INVALID_ROUNDING_PLACE_INPUT:
			std::cout<<"error: INVALID_ROUNDING_PLACE_INPUT\n";
			break;
		default:
			std::cout<<"error: ERROR CODE NOT FOUND!\n";
			break;
	}
}

error_code_t input_sanitizer(const std::vector<std::string> &value_strs, const std::regex& float_pattern) 
{
	
	for (int i = 0; i < 4; ++i)
	{
		if (std::regex_search(value_strs[i], float_pattern)) 
		{	
			if ( (abs(std::stod(value_strs[i])) >= 1.79769e+308) || (abs(std::stod(value_strs[i])) <= 2.22507e-308) )
			{				
				std::cout<<std::stod(value_strs[i])<<'\n';
				return INFINITY_REACHED;
			}
		
		} 
		else 
		{			
			return INVALID_COORD_INPUT;
		}
	}
	return NO_ERROR;
}

void set_point(point_t *pt, std::string x_value_str, std::string y_value_str)
{
	pt->x = std::stod(x_value_str);
	pt->y = std::stod(y_value_str);
}

double round_to_specific_place(double value, int rounding_place) {
    double f = std::pow(10.0, rounding_place);  
    return std::round(value * f) / f;
}

result_t calculateSlope(point_t *pt1, point_t *pt2, int rounding_place)
{
	result_t result;
	double   numerator, denominator;

	//dev-test
	std::cout << "\n[dev-test] raw point values\n------------\n";
	std::cout << '|' << pt1->x << '\n';
	std::cout << '|' << pt1->y << '\n';
	std::cout << '|' << pt2->x << '\n';
	std::cout << '|' << pt2->y << '\n';
	// std::cout << "\n------------\n";

	numerator   = pt2->y - pt1->y;
	denominator = pt2->x - pt1->x;
	if ((int)denominator == 0)
	{
		result.error_code = DIV_BY_ZERO;
		return result;
	}
	result.error_code = NO_ERROR;
	result.value      = round_to_specific_place(numerator/denominator, rounding_place);
	return result;
}

int main(int argc, char *argv[])
{
	//input format: <x1> <y1> <x2> <y2> <rounding_place>
	
	std::regex float_pattern(R"([0-9]+\.[0-9]+(?:e[+-]?[0-9]{1,308})?)");

	std::vector<std::string> value_strs = {argv[X1_VALUE], argv[Y1_VALUE], argv[X2_VALUE], argv[Y2_VALUE]};
	
	//dev-test
	std::cout << "\n[dev-test] raw string values\n------------\n";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << '|' << value_strs[i]<<'\n';
	}
	// std::cout << "\n------------\n";

	error_code_t value_input_check = input_sanitizer(value_strs, float_pattern);

	if (value_input_check != NO_ERROR)
	{
		print_error_code(value_input_check);
		return 1;
	}

	int rounding_place;
	try
	{
		rounding_place = std::stoi(argv[ROUNDING_PLACE]);	
	}
	catch (...)
	{
		print_error_code(INVALID_ROUNDING_PLACE_INPUT);
	}

	if (rounding_place < 0 || rounding_place >= 16)
	{
		std::cout<<"[ERROR] Rounding place range is strictly [0,15] \n";
		print_error_code(INVALID_ROUNDING_PLACE_INPUT);
		return 1;
	}
	
	std::cout<<rounding_place<<'\n';
	point_t pt1, pt2;
	set_point(&pt1, argv[X1_VALUE], argv[Y1_VALUE]);
	set_point(&pt2, argv[X2_VALUE], argv[Y2_VALUE]);

	result_t answer = calculateSlope(&pt1, &pt2, rounding_place);
	if (answer.error_code != NO_ERROR)
	{
		print_error_code(answer.error_code);
		return 1;
	}
	std::cout<<"Slope is: " << answer.value <<'\n';
	return 0;
}
