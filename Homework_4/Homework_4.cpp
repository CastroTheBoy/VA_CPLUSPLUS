#include <iostream>
#include <limits>
#include "TriangleInequalityException.hpp"
#include "Triangle.hpp"

double getSide(int number) {
    double temp;
    std::cout << "Please enter an real number between for side " << number << " (use dot as decimal delimiter): ";
    while (true) {
        if (std::cin >> temp) {
            return temp;
        }
        else {
            // Reset failure flags and flush buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, try again: ";
        }
    }
}

int main()
{
    // initializing to a nullptr so compiler doesn't complain about accessing uninitialized variable
    Triangle* triangle = nullptr;
    while (true) {
        double sideOne = getSide(1);
        double sideTwo = getSide(2);
        double sideThree = getSide(3);
        try {
            triangle = new Triangle(sideOne, sideTwo, sideThree);
            break;
        }
        catch (TriangleInequalityException e) {
            std::cout << e.what() << " Please input triangle sides again." << '\n';
        }
    }

    triangle->Print();
    triangle->Change(1,1,1);
    triangle->Print();
    triangle->Calculation();

    delete triangle;

    std::cout << '\n' << "Press Enter to close the program" << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getchar(); // For compiled versions so that console doesn't close immediatelly
}