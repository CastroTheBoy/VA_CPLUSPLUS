#include "TriangleInequalityException.hpp"
#include <iostream>

TriangleInequalityException::TriangleInequalityException(double sideOne, double sideTwo, double sideThree) {
	this->sideOne = sideOne;
	this->sideTwo = sideTwo;
	this->sideThree = sideThree;
}

std::vector<double> TriangleInequalityException::getSides() const {
	return std::vector<double> { sideOne, sideTwo, sideThree };
}