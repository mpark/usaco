/*
   ID:   michael119
   PROG: skidesign
   LANG: C++14
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

int cost_to_fit(int lo, int hi, const vector<int> &hills) {
  int cost = 0;
  for (int hill : hills) {
    if (lo <= hill && hill <= hi) {
      continue;
    }
    int diff = min(abs(lo - hill), abs(hi - hill));
    cost += diff * diff;
  }
  return cost;
};

int main() {
  ifstream in("skidesign.in");
  ofstream out("skidesign.out");

  int n;
  in >> n;

  vector<int> hills(n);
  for (int i = 0; i < n; ++i) {
    in >> hills[i];
  }

  sort(hills.begin(), hills.end());

  int min_cost = numeric_limits<int>::max();
  for (int lo = hills.front(); lo <= hills.back() - 17; ++lo) {
    min_cost = min(min_cost, cost_to_fit(lo, lo + 17, hills));
  }

  out << min_cost << '\n';
}
