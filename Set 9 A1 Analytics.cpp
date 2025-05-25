#include "StringGenerator.h"
#include "SortTester.h"
#include "StringSorters.h"
#include <algorithm>
#include <vector>
#include <string>

int main() {
  StringGenerator generator(10, 200);
  generator.setMaxPoolSize(3000);

  SortTester tester("results.csv");

  tester.addSorter("std::sort", [](std::vector<std::string>& a) {
    std::sort(a.begin(), a.end());
    });
  tester.addSorter("std::stable_sort", [](std::vector<std::string>& a) {
    std::stable_sort(a.begin(), a.end());
    });
  tester.addSorter("quick3way", sort_string_quick_3way);
  tester.addSorter("merge_lcp", sort_string_merge_lcp);
  tester.addSorter("msd_radix", sort_msd_radix);
  tester.addSorter("msd_radix_quick", sort_msd_radix_quick);

  std::vector<std::size_t> sizes = { 100, 500, 1000, 2000, 3000 };
  std::vector<StringGenerator::OrderType> orders = {
      StringGenerator::OrderType::RANDOM,
      StringGenerator::OrderType::REVERSED,
      StringGenerator::OrderType::ALMOST_SORTED
  };

  tester.run(generator, sizes, orders);

  return 0;
}

