/*
 * stem_and_leaf.cpp
 *
 *  Created on: Oct 30, 2020
 *      Author: jonesy
 */


#include <vector>
#include "stem_and_leaf.h"

Stem_and_Leaf::Stem_and_Leaf()
{
  data_values = {};
  number_of_values = 0;
  number_of_rows = 0;
}

Stem_and_Leaf::Stem_and_Leaf(std::vector<float> dv)
{
  data_values = dv;
  number_of_values = 0;
  number_of_rows = 0;
}

void Stem_and_Leaf::init_table()
{
  int stem_index = 0;
  int value = 0;
  int stem = 0;
  int leaf = 0;

  number_of_values = size(data_values);

  for (int leaf_index = 0; leaf_index < number_of_values; leaf_index++)
  {
    value = data_values[leaf_index];
    leaf = find_leaf(value);
    stem = find_stem(value);

    if (leaf_index == 0)
    {
      create_row(stem, leaf);
    }
    else
    {
      if (stem == stems_and_leaves[stem_index][0])
      {
        stems_and_leaves[stem_index].push_back(leaf);
      }
      else
      {
        create_row(stem, leaf);
        stem_index++;
      }
    }
  }

  number_of_rows = stem_index + 1;
}

int Stem_and_Leaf::find_leaf(int value)
{
  std::string x = std::to_string(value);
  int leaf = std::stoi(&x.back());

  return leaf;
}

int Stem_and_Leaf::find_stem(int value)
{
  std::string x = std::to_string(value);
  x.pop_back();
  int stem = std::stoi(x);

  return stem;
}

void Stem_and_Leaf::create_row(int s, int l)
{
  std::vector<int> new_row;
  new_row.push_back(s);
  new_row.push_back(l);
  stems_and_leaves.push_back(new_row);
}

int Stem_and_Leaf::get_number_of_values()
{
  return number_of_values;
}

int Stem_and_Leaf::get_number_of_rows()
{
  return number_of_rows;
}

std::vector<int> Stem_and_Leaf::get_leaves_of_stem(int stem_index)
{
  return stems_and_leaves[stem_index];
}



