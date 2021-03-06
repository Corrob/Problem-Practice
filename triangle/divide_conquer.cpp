#include <iostream>
#include <map>
#include <vector>

struct Point {
  Point(int one, int two) {
    x = one;
    y = two;
  }
  int x;
  int y;
};

unsigned long long tri_count(int w, int h);
bool is_triangle(Point one, Point two, Point three);

int main() {
  std::cout << "1x1 (Expected 4): " << tri_count(1, 1) << "\n\n";
  std::cout << "1x2 (Expected 18): " << tri_count(1, 2) << "\n\n";
  std::cout << "3x3 (Expected 516): " << tri_count(3, 3) << "\n\n";
  std::cout << "4x4 (Expected 2148): " << tri_count(4, 4) << "\n\n";
  std::cout << "10x9 (Expected 210234): " << tri_count(10, 9) << "\n\n";
  return 0;
}

unsigned long long tri_count(int w, int h) {
  static std::map<std::pair<int, int>, unsigned long long> memo;
  if (w == 0 || h == 0) {
    return 0;
  } else if (memo.count(std::make_pair(w, h)) > 0) {
    return memo[std::make_pair(w, h)];
  }

  unsigned long long count = 0;
  if (w % 2 == 0) {
    count += tri_count(w / 2, h);
    count += tri_count(w / 2 - 1, h);
  } else {
    count += 2 * tri_count(w / 2, h);
  }

  std::vector<Point> left_points;
  for (int i = 0; i <= w / 2; i++) {
    for (int j = 0; j <= h; j++) {
      left_points.push_back(Point(i, j));
    }
  }

  std::vector<Point> right_points;
  for (int i = w / 2 + 1; i <= w; i++) {
    for (int j = 0; j <= h; j++) {
      right_points.push_back(Point(i, j));
    }
  }

  for (int i = 0; i < left_points.size(); i++) {
    for (int j = 0; j < right_points.size(); j++) {
      for (int k = j + 1; k < right_points.size(); k++) {
        if (is_triangle(left_points.at(i), right_points.at(j), right_points.at(k)))
          count++;
      }
    }
  }

  for (int i = 0; i < right_points.size(); i++) {
    for (int j = 0; j < left_points.size(); j++) {
      for (int k = j + 1; k < left_points.size(); k++) {
        if (is_triangle(right_points.at(i), left_points.at(j), left_points.at(k)))
          count++;
      }
    }
  }

  memo[std::make_pair(w, h)] = count;
  return count;
}

bool is_triangle(Point one, Point two, Point three) {
  if (one.x == two.x &&
      two.x == three.x) return false;
  if (one.y == two.y &&
      two.y == three.y) return false;

  int dx1 = two.x - one.x;
  int dy1 = two.y - one.y;
  int dx2 = three.x - one.x;
  int dy2 = three.y - one.y;
  if (dy1 * dx2 == dy2 * dx1) return false;

  return true;
}
