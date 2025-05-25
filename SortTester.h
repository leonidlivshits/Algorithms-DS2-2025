#pragma once

#include <string>
#include <vector>
#include <functional>
#include "StringGenerator.h"

class SortTester {
public:
  using SortFunc = std::function<void(std::vector<std::string>&)>;

  explicit SortTester(const std::string& outputFilename, int runs = 5);

  void addSorter(const std::string& name, SortFunc sorter);

  void run(const StringGenerator& generator,
    const std::vector<std::size_t>& sizes,
    const std::vector<StringGenerator::OrderType>& orders);

private:
  std::string outputFilename_;
  int runs_;
  std::vector<std::pair<std::string, SortFunc>> sorters_;
};
