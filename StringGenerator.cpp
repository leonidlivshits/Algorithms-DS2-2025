#include "StringGenerator.h"
#include <algorithm>

StringGenerator::StringGenerator(int minLen, int maxLen)
  : minLen_(minLen)
  , maxLen_(maxLen)
  , engine_(std::random_device{}())
  , lenDist_(minLen_, maxLen_)
  , charDist_(0, static_cast<int>(ALPHABET.size()) - 1)
  , maxPoolSize_(3000)
{
}

void StringGenerator::setMaxPoolSize(std::size_t maxPoolSize) {
  maxPoolSize_ = maxPoolSize;
}

std::vector<std::string> StringGenerator::generatePool() const {
  std::vector<std::string> pool;
  pool.reserve(maxPoolSize_);
  for (std::size_t i = 0; i < maxPoolSize_; ++i) {
    pool.emplace_back(randomString());
  }
  std::sort(pool.begin(), pool.end());
  return pool;
}

std::vector<std::string> StringGenerator::generate(
  std::size_t size,
  OrderType order) const
{
  auto pool = generatePool();
  if (size > pool.size()) {
    size = pool.size();
  }
  std::vector<std::string> arr(pool.begin(), pool.begin() + size);

  switch (order) {
  case OrderType::RANDOM:
    std::shuffle(arr.begin(), arr.end(), engine_);
    break;
  case OrderType::REVERSED:
    std::reverse(arr.begin(), arr.end());
    break;
  case OrderType::ALMOST_SORTED:
    createAlmostSorted(arr);
    break;
  }
  return arr;
}

std::string StringGenerator::randomString() const {
  int length = lenDist_(engine_);
  std::string s;
  s.reserve(length);
  for (int i = 0; i < length; ++i) {
    s.push_back(ALPHABET[charDist_(engine_)]);
  }
  return s;
}

void StringGenerator::createAlmostSorted(std::vector<std::string>& arr) const {
  std::size_t n = arr.size();
  std::size_t swaps = n / 20 + 1;
  std::uniform_int_distribution<std::size_t> posDist(0, n - 1);
  for (std::size_t i = 0; i < swaps; ++i) {
    std::size_t a = posDist(engine_), b = posDist(engine_);
    std::swap(arr[a], arr[b]);
  }
}
