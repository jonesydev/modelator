/*
 * frequencyTable.cpp
 *
 *  Created on: Oct 4, 2020
 *      Author: jonesy
 */


#include <vector>
#include <string>

#include "frequency_row.h"


Frequency_Row::Frequency_Row()
{
  data_value = 0.0;
  frequency = 0;
  relative_frequency = 0.0;
  cumulative_relative_frequency = 0.0;
  is_grouped = false;
  interval = 0.0;
  z_score = 0.0;
}


Frequency_Row::Frequency_Row(float val=0.0,
		                         int freq=0,
			                       float rel_freq=0.0,
			                       float cum_rel_freq=0.0,
				                     bool is_grp=false,
				                     float intrvl=0.0)
{
  data_value = val;
  frequency = freq;
  relative_frequency = rel_freq;
  cumulative_relative_frequency = cum_rel_freq;
  is_grouped = is_grp;
  interval = intrvl;
  z_score = 0.0;
}

void Frequency_Row::set_data_value(float dv_num)
{
  data_value = dv_num;
}

void Frequency_Row::set_data_value(std::string& dv_str)
{
  data_value_str = dv_str;
}

float Frequency_Row::get_data_value()
{
  return data_value;
}


std::string Frequency_Row::get_data_value_string()
{
  return data_value_str;
}


int Frequency_Row::get_frequency()
{
  return frequency;
}


void Frequency_Row::set_frequency(int f)
{
  frequency = f;
}


float Frequency_Row::get_relative_frequency()
{
  return relative_frequency;
}


void Frequency_Row::set_relative_frequency(float rf)
{
  relative_frequency = rf;
}


float Frequency_Row::get_cumulative_relative_frequency()
{
  return cumulative_relative_frequency;
}


void Frequency_Row::set_cumulative_relative_frequency(float crf)
{
  cumulative_relative_frequency = crf;
}

void Frequency_Row::increment_frequency()
{
  int freq = get_frequency();
  set_frequency(++freq);
}

float Frequency_Row::get_z_score()
{
  return z_score;
}

void Frequency_Row::set_z_score(float z)
{
  z_score = z;
}



