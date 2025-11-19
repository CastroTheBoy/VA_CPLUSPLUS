#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
protected:
	double sideOne, sideTwo, sideThree;

	bool IsTriangleValid(double sideOne, double sideTwo, double sideThree) const;

public:
	~Triangle();

	// Will throw TriangleInequalityException if a triangle violating triangle inequality is trying to be created
	Triangle(double sideOne, double sideTwo, double sideThree);

	void Print() const;
	
	// Returns bool indicating success of alteration
	// Sides can be negative, but a change resulting in triangle inequality being violated will cancel the entire operation and return false
	bool Change(double sideOneAlterAmount, double sideTwoAlterAmount, double sideThreeAlterAmount);

	void Calculation() const;
};

#endif