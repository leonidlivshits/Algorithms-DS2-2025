#include "SortTester.h"
#include <fstream>
#include <chrono>

SortTester::SortTester(const std::string& outputFilename, int runs)
  : outputFilename_(outputFilename)
  , runs_(runs)
{
  std::ofstream out(outputFilename_, std::ios::trunc);
  out << "Sorter,Size,Order,AvgTimeMs" << '\n';
}

void SortTester::addSorter(const std::string& name, SortFunc sorter) {
  sorters_.emplace_back(name, std::move(sorter));
}

void SortTester::run(const StringGenerator& generator,
  const std::vector<std::size_t>& sizes,
  const std::vector<StringGenerator::OrderType>& orders)
{
  std::ofstream out(outputFilename_, std::ios::app);

  for (auto size : sizes) {
    int currentRuns = runs_ + (size == 3000 ? 5 : 0);

    for (auto order : orders) {
      std::vector<std::vector<std::string>> samples;
      samples.reserve(currentRuns);
      for (int r = 0; r < currentRuns; ++r) {
        samples.push_back(generator.generate(size, order));
      }

      for (auto& [name, sorter] : sorters_) {
        double totalTime = 0.0;
        for (auto& sample : samples) {
          auto data = sample;
          auto start = std::chrono::high_resolution_clock::now();
          sorter(data);
          auto end = std::chrono::high_resolution_clock::now();
          totalTime += std::chrono::duration<double, std::milli>(end - start).count();
        }
        double avgTime = totalTime / currentRuns;

        out << name
          << ',' << size
          << ',' << static_cast<int>(order)
          << ',' << avgTime
          << '\n';
      }
    }
  }
}
