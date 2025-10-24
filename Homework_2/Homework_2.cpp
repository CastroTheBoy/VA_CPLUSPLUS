#include <iostream>
#include <string>
#include <limits>

// TASK DESCRIPTION:
// User enters a natural number n. 
// Write a recursive function that finds n-th element of Fibonacci sequence (f(n) = f(n-1) + f(n-2)).
// For example, the 6th element is 8 (f(1) = 1, f(2) = 1, f(3)=2, f(4)=3, f(5)=5, f(6)=8).

// Ta teikt, full disclosure, es vairakkart esmu redzejis so neta un praktiski atceros no galvas
unsigned long fibonacciNumber(long number) {
    if (number == 0) {
        return 0;
    }
    else if (number == 1) {
        return 1;
    }
    else {
        return fibonacciNumber(number - 2) + fibonacciNumber(number - 1);
    }
}

int main()
{
	long number;
	std::cout << "Please enter an natural number: ";
	while (true) {
		if (std::cin >> number && number > 0) {
			break;
		}
		else {
			// Reset failure flags and flush buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, try again: ";
		}
	}

	std::string numberSuffix;
	if (number != 11 && (number - 1) % 10 == 0) {
		numberSuffix = "st";
	}
	else if (number != 12 && (number - 1) % 10 == 1) {
		numberSuffix = "nd";
	}
	else if (number != 13 && (number - 1) % 10 == 2) {
		numberSuffix = "rd";
	}
	else {
		numberSuffix = "th";
	}
	
	std::cout << "The " << number << numberSuffix << " of the Fibonacci sequence is: " << fibonacciNumber(number) << '\n';

	std::cout << '\n' << "Press Enter to close the program" << '\n';
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getchar(); // For compiled versions so that console doesn't close immediatelly
}