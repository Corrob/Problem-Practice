#include <iostream>
#include <sstream>
#include <map>
#include <utility>
#include <cmath>

bool isPrime(unsigned);
void generatePrimes(std::map<std::pair<int, int>, unsigned>&);
std::string getPrimeFromCoordinate(int, int,
    std::map<std::pair<int, int>, unsigned>&);

const unsigned MAXIMUM_PRIME = 10000;

int main() {
  std::map<std::pair<int, int>, unsigned> primes;

  // Put 2 (the origin) in the map first.
  std::pair<int, int> origin(0, 0);
  primes.emplace(origin, 2);

  // Generate primes up to MAXIMUM_PRIME and add to map with coordinates.
  generatePrimes(primes);

  std::cout << "1 1 (Expected The prime at location (1,1) is 5): " <<
      getPrimeFromCoordinate(1, 1, primes) << "\n";
  std::cout << "2 2 (Expected The prime at location (2,2) is 41): " <<
      getPrimeFromCoordinate(2, 2, primes) << "\n";
  std::cout << "-2 2 (Expected The prime at location (-2,2) is 59): " <<
      getPrimeFromCoordinate(-2, 2, primes) << "\n";

  return 0;
}

bool isPrime(unsigned n) {
  if (n == 1) {
    return false;
  } else if (n < 4) {
    return true;
  } else if (n % 2 == 0) {
    return false;
  } else if (n < 9) {
    return true;
  } else if (n % 3 == 0) {
    return false;
  } else {
    unsigned r = std::floor(std::sqrt(n));
    unsigned f = 5;
    while (f <= r) {
      if (n % f == 0) {
        return false;
      }
      if (n % (f + 2) == 0) {
        return false;
      }
      f += 6;
    }
    return true;
  }
}

void generatePrimes(std::map<std::pair<int, int>, unsigned>& primes) {
  int x = 0;
  int y = 0;
  unsigned numOfXYOperationsToDo = 2;
  unsigned numOfXOperationsDone = 0;
  unsigned numOfYOperationsDone = 0;
  bool addToXY = true;
  for (unsigned i = 3; i <= MAXIMUM_PRIME; i++) {
    if (isPrime(i)) {
      if (numOfXOperationsDone + numOfYOperationsDone >=
          numOfXYOperationsToDo) {
        numOfXYOperationsToDo += 2;
        numOfXOperationsDone = 0;
        numOfYOperationsDone = 0;
        addToXY = !addToXY;
      }
      if (numOfXOperationsDone < numOfXYOperationsToDo / 2) {
        (addToXY) ? x++ : x--;
        numOfXOperationsDone++;
        std::pair<int, int> coords(x, y);
        primes.emplace(coords, i);
        continue;
      }
      if (numOfYOperationsDone < numOfXYOperationsToDo / 2) {
        (addToXY) ? y++ : y--;
        numOfYOperationsDone++;
        std::pair<int, int> coords(x, y);
        primes.emplace(coords, i);
        continue;
      }
    }
  }
}

std::string getPrimeFromCoordinate(int x, int y,
    std::map<std::pair<int, int>, unsigned>& primes) {
  std::stringstream ss;
  std::pair<int, int> coordsToCheck(x, y);

  if (primes.find(coordsToCheck) == primes.end()) {
    return "Coordinates are not in range.";
  }

  ss << "The prime at location (" << x << "," << y << ") is " <<
      primes.at(coordsToCheck) << ".";
  return ss.str();
}
