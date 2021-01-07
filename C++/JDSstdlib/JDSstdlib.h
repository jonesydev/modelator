/*
 * JDSstandard_library.h
 *
 *  Created on: Oct 12, 2020
 *      Author: jonesy
 */

#ifndef JDSSTDLIB_H_
#define JDSSTDLIB_H_

#include <vector>
#include <algorithm>
#include <cmath>

template <typename T>
std::vector<T> slice_vector(std::vector<T> &v, int f, int l)
{
  auto first = cbegin(v) + f;
  auto last = cbegin(v) + l + 1;
  std::vector<T> vec(first, last);

  return vec;
}

template <typename T>
int get_index_vector(std::vector<T> &v, float e)
{
  int index = -1;

  auto iterator = find(v.cbegin(), v.cend(), e);

  if (iterator != v.cend())
  {
    index = distance(v.cbegin(), iterator);
  }

  return index;
}


bool is_an_integer(float);

#endif /* JDSSTDLIB_H_ */
