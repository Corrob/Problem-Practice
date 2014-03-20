#include <iostream>
#include <map>
#include <set>

unsigned long tri_count(unsigned m, unsigned n);
unsigned long num_collinear_triple(unsigned m, unsigned n);
unsigned n_choose_k(unsigned n, unsigned k);
unsigned gcd(unsigned a, unsigned b);

int main() {
  std::cout << "(1x1): " << num_collinear_triple(1, 1) << "\n\n";
  std::cout << "(2x2): " << num_collinear_triple(2, 2) << "\n\n";
  std::cout << "(1x3): " << num_collinear_triple(1, 3) << "\n\n";
  std::cout << "(3x3): " << num_collinear_triple(3, 3) << "\n\n";
  std::cout << "(4x4): " << num_collinear_triple(4, 4) << "\n\n";
  std::cout << "(5x5): " << num_collinear_triple(5, 5) << "\n\n";
  std::cout << "1x1 (Expected 4): " << tri_count(1, 1) << "\n\n";
  std::cout << "1x2 (Expected 18): " << tri_count(1, 2) << "\n\n";
  std::cout << "3x3 (Expected 516): " << tri_count(3, 3) << "\n\n";
  std::cout << "4x4 (Expected 2148): " << tri_count(4, 4) << "\n\n";
  std::cout << "10x9 (Expected 210234): " << tri_count(10, 9) << "\n\n";
  // 200x200 occurs in ~40 seconds
  //std::cout << "200x200 (Expected ?): " << tri_count(200, 200) << "\n\n";
  // 377x403 occurs in ~10 minutes - currently not matching number
  //std::cout << "377x403 (Expected 593516907685600): " << tri_count(377, 403) << "\n\n";
  return 0;
}

unsigned long tri_count(unsigned m, unsigned n) {
  return n_choose_k((m + 1) * (n + 1), 3) - num_collinear_triple(m, n);
}

unsigned long num_collinear_triple(unsigned m, unsigned n) {
  static std::map<std::pair<unsigned, unsigned>, unsigned long > memo;
  if (m == 0) {
    return n_choose_k(n + 1, 3);
  } else if (n == 0) {
    return n_choose_k(m + 1, 3);
  } else if (memo.count(std::make_pair(m, n)) > 0) {
    return memo[std::make_pair(m, n)];
  }
  unsigned long num = 0;
  // Top side
  // Ex. for 2x3
  // ####
  // ####
  // 0000
  num += num_collinear_triple(m - 1, n);
  // Left side
  // Ex. for 2x3
  // ###0
  // ###0
  // ###0
  num += num_collinear_triple(m, n - 1);
  // Top left was double counted
  // Ex. for 2x3
  // ###0
  // ###0
  // 0000
  num -= num_collinear_triple(m - 1, n - 1);

  // Diagonals from bottom row to right column
  // Ex. for 2x3
  // 000#       0000       000#
  // 0000 (0)-> 000# (0)-> 00#0 (1)-> etc.
  // #000       #000       0#00
  for (unsigned x = 0; x < m; x++) {
    for (unsigned y = 0; y < n; y++) {
      num += gcd(m - x, n - y) - 1;
    }
  }

  // Bottom right spot to bottom row and right column
  // Ex. for 2x3
  // 0000    0000    0000    000#
  // 0000 or 0000 or 0000 or 000#
  // ##0#    #0##    0###    000#
  num += n_choose_k(n, 2);
  num += n_choose_k(m, 2);

  // Bottom right spot diagonals
  // Ex. for 2x3
  // 0#00       0000       00#0       0000
  // 00#0 (1)-> 0#00 (0)-> 0000 (0)-> #000 (0)-> etc.
  // 000#       000#       000#       000#
  for (int x = 1; x < n; x++) {
    for (int y = 1; y < m; y++) {
      if (x / gcd(x, y)  == x) {
        int i = 1;
        for (; i * x <= n && i * y <= m; i++);
        num += n_choose_k(i - 1, 2);
      }
    }
  }

  //if (m % 10 == 0 && n % 10 == 0)
    //std::cout << m << "x" << n << ": " << num << "\n";

  memo[std::make_pair(m, n)] = num;
  return num;
}

unsigned n_choose_k(unsigned n, unsigned k)
{
  if (k > n) return 0;
  if (k * 2 > n) k = n-k;
  if (k == 0) return 1;

  int result = n;
  for( int i = 2; i <= k; ++i ) {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}

unsigned gcd(unsigned a, unsigned b) {
  unsigned r;
  while ( b ) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}
