#include <iostream>
#include <vector>

struct Point {
  Point(int one, int two) {
    x = one;
    y = two;
  }
  int x;
  int y;
};

int tri_count(int w, int h);

int main() {
  std::cout << tri_count(1, 2) << "\n";
  return 0;
}

int tri_count(int w, int h) {
  std::vector<Point> points;
  int count = 0;

  for (int i = 0; i <= w; i++) {
    for (int j = 0; j <= h; j++) {
      points.push_back(Point(i, j));
    }
  }
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      for (int k = j + 1; k < points.size(); k++) {
        std::cout << i << ", " << j << ", " << k << "\n";
        if (points.at(i).x == points.at(j).x &&
            points.at(j).x == points.at(k).x) continue;
        if (points.at(i).y == points.at(j).y &&
            points.at(j).y == points.at(k).y) continue;
        count++;
      }
    }
  }

  return count;
}
