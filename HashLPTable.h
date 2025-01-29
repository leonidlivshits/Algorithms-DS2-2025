#ifndef HASHLP_TABLE
#define HASHLP_TABLE


#include <vector>
#include <functional>

struct Cell {
  int key;
  bool isOccupied;
  bool isDeleted;
  Cell() : key(-1), isOccupied(false), isDeleted(false) {}
};

class HashLPTable {
private:
  std::vector<Cell> cells;
  int size;
  int count;
  double loadFactorThreshold;

  void rehash() {
    int newSize = size * 2;
    std::vector<Cell> newCells(newSize);
    int oldCount = count;
    for (int i = 0; i < size; ++i) {
      if (cells[i].isOccupied && !cells[i].isDeleted) {
        int key = cells[i].key;
        int index = std::hash<int>{}(key) % newSize;
        int j = 0;
        while (j < newSize) {
          int currentIndex = (index + j) % newSize;
          if (!newCells[currentIndex].isOccupied) {
            newCells[currentIndex].key = key;
            newCells[currentIndex].isOccupied = true;
            newCells[currentIndex].isDeleted = false;
            break;
          }
          j++;
        }
      }
    }
    cells = std::move(newCells);
    size = newSize;
    count = oldCount;
  }

public:
  HashLPTable(int initialSize = 10, double threshold = 0.7)
    : cells(initialSize), size(initialSize), count(0), loadFactorThreshold(threshold) {}

  bool insert(int key) {
    if (count >= size * loadFactorThreshold) {
      rehash();
    }
    int index = std::hash<int>{}(key) % size;
    bool foundDeleted = false;
    int deletedIndex = -1;
    int i = 0;
    while (i < size) {
      int currentIndex = (index + i) % size;
      if (cells[currentIndex].isOccupied) {
        if (!cells[currentIndex].isDeleted && cells[currentIndex].key == key) {
          return false;
        }
        if (cells[currentIndex].isDeleted && !foundDeleted) {
          foundDeleted = true;
          deletedIndex = currentIndex;
        }
      }
      else {
        break;
      }
      i++;
    }
    if (foundDeleted) {
      cells[deletedIndex].key = key;
      cells[deletedIndex].isOccupied = true;
      cells[deletedIndex].isDeleted = false;
    }
    else {
      if (i == size) {
        return false;
      }
      int currentIndex = (index + i) % size;
      cells[currentIndex].key = key;
      cells[currentIndex].isOccupied = true;
      cells[currentIndex].isDeleted = false;
    }
    count++;
    return true;
  }

  bool find(int key) const {
    int index = std::hash<int>{}(key) % size;
    int i = 0;
    while (i < size) {
      int currentIndex = (index + i) % size;
      if (!cells[currentIndex].isOccupied) {
        return false;
      }
      if (cells[currentIndex].isOccupied && !cells[currentIndex].isDeleted && cells[currentIndex].key == key) {
        return true;
      }
      i++;
    }
    return false;
  }

  bool remove(int key) {
    int index = std::hash<int>{}(key) % size;
    int i = 0;
    while (i < size) {
      int currentIndex = (index + i) % size;
      if (!cells[currentIndex].isOccupied) {
        return false;
      }
      if (cells[currentIndex].isOccupied && !cells[currentIndex].isDeleted && cells[currentIndex].key == key) {
        cells[currentIndex].isDeleted = true;
        count--;
        return true;
      }
      i++;
    }
    return false;
  }

  double loadFactor() const {
    return static_cast<double>(count) / size;
  }

  int getSize() const {
    return size;
  }
};


#endif 


