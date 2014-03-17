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
  std::cout << "Count: " << tri_count(100, 100) << "\n";
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
    std::cout << i << "/" << points.size() << "\n";
    for (int j = i + 1; j < points.size(); j++) {
      for (int k = j + 1; k < points.size(); k++) {
        // Remove horizontal or vertical lines
        if (points.at(i).x == points.at(j).x &&
            points.at(j).x == points.at(k).x) continue;
        if (points.at(i).y == points.at(j).y &&
            points.at(j).y == points.at(k).y) continue;

        // Remove diagonal lines
        int dx1 = points.at(j).x - points.at(i).x;
        int dy1 = points.at(j).y - points.at(i).y;
        int dx2 = points.at(k).x - points.at(i).x;
        int dy2 = points.at(k).y - points.at(i).y;
        if (dy1 * dx2 == dy2 * dx1) continue;

        count++;
      }
    }
  }

  return count;
}
