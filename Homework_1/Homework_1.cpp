#include <iostream>
#include <limits>
#include <unordered_map>
#include <typeinfo>
#include <ctime>

// TASK DESCRIPTION:
// User enters a natural number n and integer numbers a1, a2, a3,..., an(n<100). Print out the most repetitive number and how many are they. 
// If there is more than one the most repetitive number, print out the largest. 
// For example, the sequence of numbers is 2, 9, 3, 3, 18, 5, 27, 18. The output will be: 18.

int main()
{
	int debugIdentifier = 621; // I really like AC6
	std::srand(std::time({}));

	// Input will fail on int overflow, it's fine.
	int arraySize;
	std::cout << "Please enter an natural number between 1 an 99: ";
	while (true) {
		if (std::cin >> arraySize && ((arraySize < 100 && arraySize > 0) || arraySize == debugIdentifier /* debug mode override */)) {
			break;
		} 
		else {
			// Reset failure flags and flush buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, try again: ";
		}
	}

	bool debugMode = arraySize == debugIdentifier;

	int* numberArr;
	if (debugMode) {
		numberArr = new int[arraySize];
		arraySize = std::rand() % 100;
		std::cout << "Generating a random array..." << '\n';
		for (int i = 0; i < arraySize; i++) {
			numberArr[i] = std::rand() % 20;
		}
	} 
	else {
		numberArr = new int[arraySize];
		std::cout << "Please enter values for " << arraySize << " integers." << '\n';
		for (int i = 0; i < arraySize; i++) {
			std::cout << i + 1 << ": ";
			while (true) {
				if (std::cin >> numberArr[i]) {
					break;
				}
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input, try again: ";
				}
			}
		}
	}

	std::pair<int, int> largestNumber(numberArr[0], 1);
	std::unordered_map<int, int> counterMap;
	for (int i = 0; i < arraySize; i++) {
		int& currentNumber = numberArr[i];
		const auto& numberInsert = counterMap.insert({ currentNumber, 1 });
		if (!numberInsert.second) {
			int& numberCounter = (*numberInsert.first).second;
			++numberCounter;
			// Replace if counter is less
			if (largestNumber.second < numberCounter) {
				largestNumber.first = (*numberInsert.first).first;
				largestNumber.second = (*numberInsert.first).second;
			} // Replace if same counter but larger number 
			else if (largestNumber.first < currentNumber && largestNumber.second == numberCounter) {
				largestNumber.first = (*numberInsert.first).first;
			}
		} // Replace current largest number if the counter is still 1 and loop number is larger
		else if (largestNumber.second == 1 && largestNumber.first < currentNumber) {
			largestNumber.first = currentNumber;
		}
	}

	std::cout << "Most common number: " << largestNumber.first << '\n';
	std::cout << "Appearance count: " << largestNumber.second << '\n';

	if (debugMode) {
		for (auto& ele : counterMap) {
			std::cout << ele.first << ' ' << ele.second << '\n';
		}
	}
	
	delete[] numberArr;

	std::cout << '\n' << "Press Enter to close the program" << '\n';
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getchar(); // For compiled versions so that console doesn't close immediatelly
}