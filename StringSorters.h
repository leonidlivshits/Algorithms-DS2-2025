#pragma once

#include <vector>
#include <string>
#include <algorithm>

inline int charAt(const std::string& s, int d) {
  return (d < 0 || d >= static_cast<int>(s.size())) ? -1 : static_cast<unsigned char>(s[d]);
}

inline void stringQuick3Way(std::vector<std::string>& a, int l, int r, int d) {
  if (l >= r) return;
  int lt = l, gt = r - 1, i = l + 1;
  int v = charAt(a[l], d);
  while (i <= gt) {
    int t = charAt(a[i], d);
    if (t < v) std::swap(a[lt++], a[i++]);
    else if (t > v) std::swap(a[i], a[gt--]);
    else ++i;
  }
  stringQuick3Way(a, l, lt, d);
  if (v >= 0) stringQuick3Way(a, lt, gt + 1, d + 1);
  stringQuick3Way(a, gt + 1, r, d);
}

inline void sort_string_quick_3way(std::vector<std::string>& a) {
  stringQuick3Way(a, 0, static_cast<int>(a.size()), 0);
}

inline bool lcpCompare(const std::string& a, const std::string& b) {
  int n = std::min(a.size(), b.size());
  int i = 0;
  while (i < n && a[i] == b[i]) ++i;
  if (i == n) return a.size() < b.size();
  return a[i] < b[i];
}

inline void mergeLCP(std::vector<std::string>& a, int l, int r) {
  if (l >= r - 1) return;
  int m = (l + r) / 2;
  mergeLCP(a, l, m);
  mergeLCP(a, m, r);
  std::vector<std::string> buf;
  buf.reserve(r - l);
  int i = l, j = m;
  while (i < m && j < r) {
    if (lcpCompare(a[i], a[j])) buf.push_back(std::move(a[i++]));
    else buf.push_back(std::move(a[j++]));
  }
  while (i < m) buf.push_back(std::move(a[i++]));
  while (j < r) buf.push_back(std::move(a[j++]));
  for (int k = 0; k < static_cast<int>(buf.size()); ++k) {
    a[l + k] = std::move(buf[k]);
  }
}

inline void sort_string_merge_lcp(std::vector<std::string>& a) {
  mergeLCP(a, 0, static_cast<int>(a.size()));
}

inline void msdRadix(std::vector<std::string>& a, std::vector<std::string>& aux, int l, int r, int d) {
  if (l >= r) return;
  const int R = 256;
  std::vector<int> count(R + 2, 0);
  for (int i = l; i < r; ++i) {
    int c = charAt(a[i], d) + 1;
    count[c + 1]++;
  }
  for (int i = 0; i < R + 1; ++i) count[i + 1] += count[i];
  for (int i = l; i < r; ++i) {
    int c = charAt(a[i], d) + 1;
    aux[count[c]++] = std::move(a[i]);
  }
  for (int i = l; i < r; ++i) a[i] = std::move(aux[i - l]);
  int prev = l;
  for (int i = 0; i <= R; ++i) {
    int sz = count[i + 1] - count[i];
    if (sz > 1) msdRadix(a, aux, prev, prev + sz, d + 1);
    prev += sz;
  }
}

inline void sort_msd_radix(std::vector<std::string>& a) {
  std::vector<std::string> aux(a.size());
  msdRadix(a, aux, 0, static_cast<int>(a.size()), 0);
}

inline void msdRadixQuick(std::vector<std::string>& a, std::vector<std::string>& aux, int l, int r, int d) {
  int N = r - l;
  if (N <= 1) return;
  if (N < 74) {
    stringQuick3Way(a, l, r, d);
    return;
  }
  const int R = 256;
  std::vector<int> count(R + 2, 0);
  for (int i = l; i < r; ++i) {
    int c = charAt(a[i], d) + 1;
    count[c + 1]++;
  }
  for (int i = 0; i < R + 1; ++i) count[i + 1] += count[i];
  for (int i = l; i < r; ++i) {
    int c = charAt(a[i], d) + 1;
    aux[count[c]++] = std::move(a[i]);
  }
  for (int i = l; i < r; ++i) a[i] = std::move(aux[i - l]);
  int prev = l;
  for (int i = 0; i <= R; ++i) {
    int sz = count[i + 1] - count[i];
    if (sz > 1) msdRadixQuick(a, aux, prev, prev + sz, d + 1);
    prev += sz;
  }
}

inline void sort_msd_radix_quick(std::vector<std::string>& a) {
  std::vector<std::string> aux(a.size());
  msdRadixQuick(a, aux, 0, static_cast<int>(a.size()), 0);
}
