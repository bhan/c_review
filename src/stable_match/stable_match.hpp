#ifndef STABLE_MATCH_HPP
#define STABLE_MATCH_HPP

#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class stable_match {
 public:
  template <typename A, typename B>
  static std::vector<std::pair<A,B>>
  get_stable_match(std::unordered_map<A,std::vector<B>> A_prefs,
                   std::unordered_map<B,std::vector<A>> B_prefs) {
    assert(A_prefs.size() == B_prefs.size());
    // build map for fast preference comparison
    std::unordered_map<B,std::unordered_map<A,size_t>> B_A_to_idx;
    for (auto it = B_prefs.begin(); it != B_prefs.end(); ++it) {
      std::unordered_map<A,size_t> A_to_idx; size_t cur_idx = 0;
      for (auto vit = it->second.begin(); vit != it->second.end(); ++vit) {
        A_to_idx[*vit] = cur_idx; ++cur_idx;
      }
      B_A_to_idx[it->first] = A_to_idx;
    }
    std::unordered_map<A,size_t> A_to_next_B; std::unordered_set<A> A_free;
    for (auto it = A_prefs.begin(); it != A_prefs.end(); ++it) {
      A_to_next_B[it->first] = 0; A_free.insert(it->first);
    }
    std::unordered_map<B,A> B_to_A;

    while (A_free.size() > 0) {
      A curA = *(A_free.begin());
      B proposeB = A_prefs[curA][A_to_next_B[curA]];
      ++A_to_next_B[curA];
      std::cout << curA << " propose to " << proposeB << std::endl;
      if (B_to_A.find(proposeB) == B_to_A.end()) { // proposeB is free
        std::cout << curA << " engaged to " << proposeB << std::endl;
        B_to_A[proposeB] = curA;
        A_free.erase(curA);
      } else { // proposeB is currently engaged
        A proposeA = B_to_A[proposeB]; // current partner of B
        if (B_A_to_idx[proposeB][curA] < B_A_to_idx[proposeB][proposeA]) {
          // proposeB prefers curA over proposeA
          B_to_A[proposeB] = curA;
          A_free.insert(proposeA);
          A_free.erase(curA);
          std::cout << curA << " engaged to " << proposeB << ", " << proposeA
                    << " free" << std::endl;
        } else {
          std::cout << curA << " refused by " << proposeB << std::endl;
        }
      }
    }
    assert(B_to_A.size() == A_prefs.size());
    std::vector<std::pair<A,B>> res;
    for (auto it = B_to_A.begin(); it != B_to_A.end(); ++it) {
      res.push_back({it->second,it->first});
    }
    return res;
  }
};
#endif
