#include <iostream>
#include <ctime>

int main() {
  int num;
  int guess;
  int tries;
  tries = 0;

  srand(time(NULL));
  num = rand() % 100 + 1;
  std::cout << "------ Number Guessing Game ------\n";
  do {
    std::cout << "Enter guess between (1-100): ";
    std::cin >> guess;
    tries++;

    if (guess > num) {
      std::cout << "Too high!\n";
    } else if (guess < num) std::cout << "Too low!\n";
    else std::cout << "Correct! # of tries: " << tries << std::endl;
   } while (guess != num);
   std::cout << "------- End of game --------";
  return 0;
}