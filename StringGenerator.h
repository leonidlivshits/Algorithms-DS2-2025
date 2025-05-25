#pragma once

#include <vector>
#include <string>
#include <random>

class StringGenerator {
public:
  enum class OrderType { RANDOM, REVERSED, ALMOST_SORTED };

  StringGenerator(int minLen = 10, int maxLen = 200);

  void setMaxPoolSize(std::size_t maxPoolSize);

  std::vector<std::string> generatePool() const;

  std::vector<std::string> generate(std::size_t size, OrderType order) const;

private:
  std::string randomString() const;
  void createAlmostSorted(std::vector<std::string>& arr) const;

  const int minLen_;
  const int maxLen_;
  mutable std::mt19937 engine_;
  mutable std::uniform_int_distribution<int> lenDist_;
  mutable std::uniform_int_distribution<int> charDist_;
  std::size_t maxPoolSize_;
  static inline const std::string ALPHABET =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#%:;^&*()-";
};
