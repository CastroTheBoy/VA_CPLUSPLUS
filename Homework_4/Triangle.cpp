#include "Triangle.hpp"
#include "TriangleInequalityException.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

Triangle::Triangle(double sideOne, double sideTwo, double sideThree) {
	if (!IsTriangleValid(sideOne, sideTwo, sideThree)) {
		throw TriangleInequalityException(sideOne, sideTwo, sideThree);
	}
	this->sideOne = sideOne;
	this->sideTwo = sideTwo;
	this->sideThree = sideThree;
}

Triangle::~Triangle() {
	std::cout << "Triangle object with the following sides" << "\n";
	this->Print();
	std::cout << "Has been destroyed." << "\n";
}

bool Triangle::IsTriangleValid(double sideOne, double sideTwo, double sideThree) const {
	return (sideOne + sideTwo > sideThree && sideOne + sideThree > sideTwo && sideTwo + sideThree > sideOne);
}

void Triangle::Print() const {
	std::cout << "Side one: " << sideOne << ", side two: " << sideTwo << ", side three: " << sideThree << '\n';
}

bool Triangle::Change(double sideOneAlterAmount, double sideTwoAlterAmount, double sideThreeAlterAmount) {

	if (IsTriangleValid(this->sideOne + sideOneAlterAmount, this->sideTwo + sideTwoAlterAmount, this->sideTwo + sideThreeAlterAmount)) {
		return false;
	}
	this->sideOne += sideOneAlterAmount;
	this->sideTwo += sideTwoAlterAmount;
	this->sideTwo += sideThreeAlterAmount;
	return true;
}

void Triangle::Calculation() const {
	
	auto sqrt2 = [](double side) {
		return std::pow(side, 2);
	};
	auto median = [&sqrt2](double mainSide, double sideLeft, double sideRight) {
		return std::sqrt(
			(2 * sqrt2(sideLeft) + 2 * sqrt2(sideRight) - sqrt2(mainSide)) / 4
		);
	};
	auto type = [&sqrt2](double sone, double stwo, double sthree) {
		std::vector<double> sides = { sqrt2(sone), sqrt2(stwo), sqrt2(sthree) };
		std::sort(sides.begin(), sides.end());
		auto comp = (sides[0] + sides[1]) <=> sides[2];
		if (comp < 0) {
			return "obtuse";
		}
		else if (comp == 0) {
			return "right";
		}
		else if (comp > 0) {
			return "acute";
		}
		else {
			return "undefined triangle type";
		}
	};

	double sonesq2 = sqrt2(sideOne);
	double stwosq2 = sqrt2(sideTwo);
	double sthreesq2 = sqrt2(sideThree);

	std::cout << "The first median of this triangle is: " << median(sideOne, sideTwo, sideThree) << '\n';
	std::cout << "The second median of this triangle is: " << median(sideTwo, sideOne, sideThree) << '\n';
	std::cout << "The third median of this triangle is: " << median(sideThree, sideOne, sideTwo) << '\n';
	std::cout << "This triangle is " << type(sideThree, sideOne, sideTwo) << " angled" << '\n';
}