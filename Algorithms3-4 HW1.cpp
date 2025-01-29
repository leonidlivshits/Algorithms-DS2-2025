#include <cassert>
#include <iostream>
#include "HashLPTable.h"
#include <cassert>
#include <iostream>

void testInsertAndFind() {
  HashLPTable table;
  assert(table.insert(5));
  assert(table.find(5));
  assert(!table.find(10));
}

void testRemove() {
  HashLPTable table;
  table.insert(5);
  assert(table.remove(5));
  assert(!table.find(5));
  assert(!table.remove(5));
}

void testRehash() {
  HashLPTable table(5, 0.6);
  table.insert(1);
  table.insert(2);
  table.insert(3);
  assert(table.getSize() == 5);
  table.insert(4);
  assert(table.getSize() == 10);
  assert(table.find(1));
  assert(table.find(2));
  assert(table.find(3));
  assert(table.find(4));
}

void testCollision() {
  HashLPTable table(5);
  table.insert(1);
  table.insert(6);
  assert(table.find(1));
  assert(table.find(6));
}

void testDeletedInsert() {
  HashLPTable table;
  table.insert(10);
  table.remove(10);
  assert(table.insert(10));
  assert(table.find(10));
}

void testLoadFactor() {
  HashLPTable table(10, 0.7);
  for (int i = 0; i < 7; ++i) table.insert(i);
  assert(table.loadFactor() == 0.7);
  table.insert(7);
  assert(table.getSize() == 20);
  assert(table.loadFactor() == 0.4);
}

void testInsertAfterFullDeletion() {
  HashLPTable table(3, 1.0);
  table.insert(1);
  table.insert(2);
  table.insert(3);
  table.remove(1);
  table.remove(2);
  table.remove(3);
  assert(table.insert(4));
  assert(table.find(4));
}

int main() {
  testInsertAndFind();
  testRemove();
  testRehash();
  testCollision();
  testDeletedInsert();
  testLoadFactor();
  testInsertAfterFullDeletion();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}