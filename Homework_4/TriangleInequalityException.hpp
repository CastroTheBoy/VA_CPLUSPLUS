#ifndef TRIANGLE_INEQUALITY_EXCEPTION_H
#define TRIANGLE_INEQUALITY_EXCEPTION_H
#include <exception>
#include <vector>

class TriangleInequalityException : public std::exception {
	double sideOne, sideTwo, sideThree;

public:
	TriangleInequalityException(double sideOne, double sideTwo, double sideThree);

	const char* what() const noexcept override {
		return "Triangle inequality violated!";
	}

	std::vector<double> getSides() const;
	
};

#endif