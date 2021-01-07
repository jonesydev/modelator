/*
 * data_bin.cpp
 *
 *  Created on: Oct 28, 2020
 *      Author: jonesy
 */

#include <vector>
#include <numeric>
#include "data_bin.h"

Data_Bin::Data_Bin()
{
  bound_lower = 0.0;
  bound_upper = 0.0;
  bin_midpoint = 0.0;
  bin_frequency = 0;
}

Data_Bin::Data_Bin(float bl, float bu)
{
  bound_lower = bl;
  bound_upper = bu;
  bin_midpoint = 0.0;
  bin_frequency = 0;
}

void Data_Bin::set_bound_lower(float bl)
{
  bound_lower = bl;
}

void Data_Bin::set_bound_upper(float bu)
{
  bound_upper = bu;
}

void Data_Bin::set_bin_frequency(int bf)
{
  bin_frequency = bf;
}

void Data_Bin::add_to_bin_frequency(int bf)
{
  bin_frequency += bf;
}

int Data_Bin::get_bin_frequency()
{
  return bin_frequency;
}

float Data_Bin::get_bin_midpoint()
{
  return bin_midpoint;
}

void Data_Bin::find_bin_midpoint()
{
  bin_midpoint = (bound_lower + bound_upper) / 2;
}
