/*
   ID:   michael119
   PROG: wormhole
   LANG: C++14
*/

// Given N wormholes, where 2 <= N <= 12, N is even. Wormholes are paired up.
// The maximum # of configurations is 12! / ((2^6) * 6!) = 10,395.
// For each configuration, we need to try running bessie starting from each
// of the N wormholes. So, we get 10,395 * 12 = 124,740.

#include <algorithm>
#include <fstream>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;
using Link = pair<Point, Point>;
using Config = set<Link>;

vector<Config> compute_configs(set<Point> points) {
  if (points.size() == 0) {
    return {{}};
  }

  auto x = *begin(points);
  points.erase(x);

  vector<Config> result;

  for (auto y : points) {
    auto tail = points;
    tail.erase(y);

    auto configs = compute_configs(tail);
    for (auto &pairs : configs) {
      pairs.emplace(x, y);
      pairs.emplace(y, x);
    }

    result.insert(end(result), begin(configs), end(configs));
  }

  return result;
}

bool can_cycle_starting_at(const Config &config,
                           const Point &start,
                           std::set<Point> &visited) {
  if (visited.find(start) != end(visited)) {
    return true;
  }

  visited.insert(start);

  for (const auto &link : config) {
    const auto &from = link.first;
    const auto &to = link.second;

    if (start.second == from.second && start.first < from.first) {
      return can_cycle_starting_at(config, to, visited);
    }
  }

  return false;
}

bool can_cycle(const Config &config, const set<Point> &points) {
  return std::any_of(begin(points), end(points), [&](const auto &start) {
    std::set<Point> visited;
    return can_cycle_starting_at(config, start, visited);
  });
}

int main() {
  ifstream in("wormhole.in");
  ofstream out("wormhole.out");

  int n;
  in >> n;

  int x, y;

  set<Point> points;
  for (int i = 0; i < n; ++i) {
    in >> x >> y;
    points.emplace(x, y);
  }

  auto configs = compute_configs(points);

  out << count_if(begin(configs), end(configs), [&](const auto &config) {
    return can_cycle(config, points);
  }) << '\n';
}
