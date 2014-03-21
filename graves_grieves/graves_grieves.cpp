#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>

std::string findInitialOrder(std::vector<unsigned>);

int main() {
  std::vector<unsigned> firstCase;
  unsigned firstCasePositions[] = {0, 1, 0};
  firstCase.insert(firstCase.begin(), firstCasePositions,
      firstCasePositions + 3);

  std::vector<unsigned> secondCase;
  unsigned secondCasePositions[] = {0, 1, 2, 0, 1};
  secondCase.insert(secondCase.begin(), secondCasePositions,
      secondCasePositions + 5);

  std::cout << "{0, 1, 0} (Expected 2 1 3): " <<
      findInitialOrder(firstCase) << "\n";
  std::cout << "{0, 1, 2, 0, 1} (Expected 3 2 1 5 4): " <<
      findInitialOrder(secondCase) << "\n";

  return 0;
}

std::string findInitialOrder(std::vector<unsigned> howFarToLeftList) {
  std::list<unsigned> orderedPositions;
  for (unsigned i = 1; i <= howFarToLeftList.size(); i++) {
    orderedPositions.push_back(i);
  }

  std::list<unsigned>::iterator orderedPosIt = orderedPositions.begin();
  for (std::vector<unsigned>::iterator commandListIt = howFarToLeftList.begin();
      commandListIt != howFarToLeftList.end(); commandListIt++) {
    if (*commandListIt != 0) {
      unsigned erasedValue = *orderedPosIt;
      orderedPositions.erase(orderedPosIt);
      std::advance(orderedPosIt, -(int)*commandListIt);
      orderedPositions.insert(orderedPosIt, erasedValue);
      std::advance(orderedPosIt, *commandListIt - 1);
    }
    orderedPosIt++;
  }

  std::ostringstream stringToReturn;
  for (std::list<unsigned>::iterator it = orderedPositions.begin();
      it != orderedPositions.end(); it++) {
    stringToReturn << *it << " ";
  }
  stringToReturn << "\n";
  return stringToReturn.str();
}
