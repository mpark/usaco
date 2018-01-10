/*
   ID:   michael119
   PROG: combo
   LANG: C++
*/

// 3-tuples where each element is within range [1..N], 1 <= N <= 100.
// Should be able to test 100 * 100 * 100 = 1,000,000 cases pretty easily.

#include <cmath>
#include <fstream>

// n = 6
//
//     1   2
//  6         3
//     5   4
//

bool is_close_enough(int n, int x, int y) {
  int distance = std::abs(x - y);
  return distance <= 2 || (n - distance) <= 2;
}

int main() {
  std::ifstream in("combo.in");
  std::ofstream out("combo.out");
  int n;
  int john[3];
  int master[3];
  in >> n;
  in >> john[0] >> john[1] >> john[2];
  in >> master[0] >> master[1] >> master[2];
  int result = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= n; ++k) {
        if ((is_close_enough(n, john[0], i) &&
             is_close_enough(n, john[1], j) &&
             is_close_enough(n, john[2], k)) ||
            (is_close_enough(n, master[0], i) &&
             is_close_enough(n, master[1], j) &&
             is_close_enough(n, master[2], k))) {
          ++result;
        }
      }
    }
  }
  out << result << '\n';
}
