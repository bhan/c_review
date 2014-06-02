#include <iostream>
#include <string>

#include "stable_match.hpp"

int main() {
  std::unordered_map<std::string,std::vector<std::string>> A_prefs;
  A_prefs["mA"] = { "wC","wB","wA" };
  A_prefs["mB"] = { "wB","wA","wC" };
  A_prefs["mC"] = { "wC","wB","wA" };
  std::unordered_map<std::string,std::vector<std::string>> B_prefs;
  B_prefs["wA"] = { "mC","mA","mB" };
  B_prefs["wB"] = { "mC","mA","mB" };
  B_prefs["wC"] = { "mA","mB","mC" };
  auto pairings = stable_match::get_stable_match(A_prefs, B_prefs);
  for (auto it = pairings.begin(); it != pairings.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")" << std::endl;
  }
}
