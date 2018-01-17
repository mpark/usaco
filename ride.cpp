/*
   ID:   michael119
   PROG: ride
   LANG: C++14
*/

#include <fstream>
#include <numeric>

using namespace std;

int main() {
  ifstream in("ride.in");
  ofstream out("ride.out");

  string group;
  string comet;

  in >> group >> comet;

  auto op = [](int result, char elem) {
    return result * static_cast<int>(elem - 'A' + 1);
  };

  int group_number = accumulate(group.begin(), group.end(), 1, op) % 47;
  int comet_number = accumulate(comet.begin(), comet.end(), 1, op) % 47;

  out << (group_number == comet_number ? "GO" : "STAY") << '\n';
}
