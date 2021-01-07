/*
 * frequencyTable.cpp
 *
 *  Created on: Oct 5, 2020
 *      Author: jonesy
 */


#include <iostream>  // Likely just temporary for error handling.
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "frequency_table.h"
#include "frequency_row.h"
#include "data_bin.h"
#include "JDSstdlib.h"


Frequency_Table::Frequency_Table()
{
  data_values = {};
  rows = {};
  bins = {};
  is_grouped = false;
  number_of_intervals = 0;
  number_of_values = 0;
  number_of_rows = 0;
  size_of_interval = 0.0;
  interval_start_offset = 0.0;
  interval_start_value = 0.0;
  interval_end_value = 0.0;
  median = 0.0;
  mean = 0.0;
  mode = {};
  iqr = 0.0;
  min_value = 0.0;
  max_value = 0.0;
  quartile_1 = 0.0;
  quartile_2 = 0.0;
  quartile_3 = 0.0;
  outlier_threshhold_high = 0.0;
  outlier_threshhold_low = 0.0;
  standard_deviation = 0.0;
}

Frequency_Table::Frequency_Table(std::vector<float> dv)
{
  data_values = dv;
  rows = {};
  bins = {};
  is_grouped = false;
  number_of_intervals = 0;
  number_of_values = size(dv);
  number_of_rows = 0;
  size_of_interval = 0.0;
  interval_start_offset = 0.0;
  interval_start_value = 0.0;
  interval_end_value = 0.0;
  median = 0.0;
  mean = 0.0;
  mode = {};
  iqr = 0.0;
  min_value = 0.0;
  max_value = 0.0;
  quartile_1 = 0.0;
  quartile_2 = 0.0;
  quartile_3 = 0.0;
  outlier_threshhold_high = 0.0;
  outlier_threshhold_low = 0.0;
  standard_deviation = 0.0;
}


void Frequency_Table::init_table()
{
  create_frequency_rows();
  find_min_value();
  find_max_value();

  if (is_grouped)
  {
    set_number_of_intervals_default();
    set_interval_start_offset(interval_start_offset_tenths);
    set_up_intervals();
  }

  find_mean();
  median = find_median(data_values);
  find_mode();
  find_quartile(Quartile::first);
  find_quartile(Quartile::second);
  find_quartile(Quartile::third);
  iqr = get_IQR();
  find_outlier_threshhold_high();
  find_outlier_threshhold_low();
  find_standard_deviation();
  find_z_score();
}

void Frequency_Table::create_row(int i)
{
  Frequency_Row row{data_values[i], 1, 0.0, 0.0, is_grouped, 0.0};
  rows.push_back(row);
}

void Frequency_Table::set_is_grouped(bool ig)
{
  is_grouped = ig;
}

int Frequency_Table::get_number_of_values()
{
  return number_of_values;
}

bool Frequency_Table::is_new_table_value(int i)
{
  return data_values[i] == data_values[i - 1];
}

void Frequency_Table::set_number_of_intervals_default()
{
  number_of_intervals = round(sqrt(number_of_values));
}

void Frequency_Table::set_number_of_intervals(int n)
{
  number_of_intervals = n;
}

float Frequency_Table::get_interval_start_offset()
{
  return interval_start_offset;
}

void Frequency_Table::set_interval_start_offset(float spo)
{
  interval_start_offset = spo;
}

float Frequency_Table::get_interval_start_value()
{
  return interval_start_value;
}

float Frequency_Table::get_interval_end_value()
{
  return interval_end_value;
}

void Frequency_Table::set_up_intervals()
{
  find_size_of_interval();
  find_interval_boundaries();
  init_data_bins();
}

int Frequency_Table::get_number_of_intervals()
{
  return number_of_intervals;
}

void Frequency_Table::find_interval_start_and_end()
{
  interval_start_value = min_value - interval_start_offset;
  interval_end_value = max_value + interval_start_offset;
}

void Frequency_Table::find_size_of_interval()
{
  find_interval_start_and_end();
  size_of_interval = ceil((interval_end_value - interval_start_value) / number_of_intervals);
}

int Frequency_Table::get_size_of_interval()
{
  return size_of_interval;
}

std::vector<float> Frequency_Table::get_interval_boundaries()
{
  return interval_boundaries;
}

std::vector<Data_Bin> Frequency_Table::get_data_bins()
{
  return bins;
}

void Frequency_Table::find_interval_boundaries()
{
  interval_boundaries.push_back(interval_start_value);

  for (int i = 1; i < number_of_intervals; i++)
  {
    interval_boundaries.push_back(interval_boundaries[i - 1] + size_of_interval);
  }

  interval_boundaries.push_back(interval_end_value);
}

bool Frequency_Table::is_within_interval(int i, int j)
{
  return ((rows[j].get_data_value() > interval_boundaries[i]) && (rows[j].get_data_value() < interval_boundaries[i + 1]));
}

void Frequency_Table::init_data_bins()
{
  int i = 0;
  int j = 0;

  create_data_bins();

  for (i = 0; i < number_of_intervals; i++)
  {
    while (is_within_interval(i, j))
    {
      bins[i].add_to_bin_frequency(rows[j].get_frequency());
      j++;
    }
  }
}

void Frequency_Table::create_data_bins()
{
  for (int i = 0; i < number_of_intervals; i++)
  {
    Data_Bin bin(interval_boundaries[i], interval_boundaries[i + 1]);
    bin.find_bin_midpoint();
    bins.push_back(bin);
  }
}

void Frequency_Table::create_frequency_rows()
{
  int row_count = 0;

  // Sort the data item values in ascending order.
  sort(begin(data_values), end(data_values));

  // Create all of the rows, populate data value and frequency.
  for (int i = 0; i < number_of_values; i++)
  {
    // This will be the first row.
    if (i == 0)
    {
      create_row(i);
      row_count++;
    }
    // All subsequent rows.
    else
    {
      if (is_new_table_value(i))
      {
        // Since the data value has occurred before, update the frequency count of the row that already exists.
        rows[row_count - 1].increment_frequency();
      }
      // If this data value has not occurred before, give it a new row.
      else
      {
        create_row(i);
        row_count++;
      }
    }
  }

  number_of_rows = size(rows);
  find_relative_frequency();
  find_cumulative_relative_frequency();
}

std::vector<Frequency_Row> Frequency_Table::get_rows()
{
  return rows;
}

float Frequency_Table::get_mean()
{
  return mean;
}

void Frequency_Table::find_mean()
{
  float total = 0.0;

  if (!is_grouped)
  {
    total = find_mean_items();
  }
  else
  {
    total = find_mean_intervals();
  }

  mean = total / number_of_values;
}

float Frequency_Table::find_mean_items()
{
  float total = 0.0;

  for (float dv : data_values)
  {
    total += dv;
  }

  return total;
}

float Frequency_Table::find_mean_intervals()
{
  float total = 0.0;

  for (Data_Bin db : bins)
  {
    total += (db.get_bin_midpoint() * db.get_bin_frequency());
  }

  return total;
}

float Frequency_Table::get_median(std::vector<float> dv)
{
  if (!median || median == 0.0)
    {
      median = find_median(dv);
    }

    return median;
}


float Frequency_Table::find_median(std::vector<float> dv)
{
  float median_ = 0.0;
  int middle_value = 0;
  int n = size(dv);

  // Find the middle of the vector.
  middle_value = ((n + 1) / 2);

  // If there are an odd number of items in the vector,
  // the middle value is the median.
  if (n % 2 != 0)
  {
    median_ = dv[middle_value - 1];
  }
  // Otherwise the median is the average of the two
  // middle values.
  else
  {
    int mid_high = middle_value;
    int mid_low = mid_high - 1;

    median_ = ((dv[mid_low] + dv[mid_high]) / 2);
  }

  return median_;
}


// There can be more than one mode, hence the vector.
std::vector<float> Frequency_Table::get_mode()
{
//  if (size(mode) < 1)
//  {
//    find_mode();
//  }

  return mode;
}

int Frequency_Table::get_max_frequency()
{
  int max_freq = 0;

  for (Frequency_Row fr : rows)
  {
    if (fr.get_frequency() > max_freq)
    {
      max_freq = fr.get_frequency();
    }
  }

  return max_freq;
}

void Frequency_Table::collect_mode_values(int max_freq)
{
  for (Frequency_Row fr : rows)
  {
    if (fr.get_frequency() == max_freq)
    {
      mode.push_back(fr.get_data_value());
    }
  }
}

void Frequency_Table::find_mode()
{
  int max_freq = get_max_frequency();

  if (max_freq > 1)
  {
    collect_mode_values(max_freq);
  }
  else
  {
    std::clog << "There was no mode." << std::endl;
  }
}

void Frequency_Table::find_relative_frequency()
{
  float freq = 0;
  float rel_freq = 0.0;

  for (int i = 0; i < number_of_rows; i++)
  {
    freq = rows[i].get_frequency();
    rel_freq = freq / number_of_values;
    rows[i].set_relative_frequency(rel_freq);
    rel_freq = 0.0;
  }
}


void Frequency_Table::find_cumulative_relative_frequency()
{
  float cum_rel_freq = 0.0;

  for (int i = 0; i < number_of_rows; i++)
  {
    cum_rel_freq += rows[i].get_relative_frequency();
    rows[i].set_cumulative_relative_frequency(cum_rel_freq);
  }
}


float Frequency_Table::get_max_value()
{
  return max_value;
}


float Frequency_Table::get_min_value()
{
  return min_value;
}


void Frequency_Table::find_min_value()
{
  min_value =  *min_element(cbegin(data_values), cend(data_values));
}


void Frequency_Table::find_max_value()
{
  max_value =  *max_element(cbegin(data_values), cend(data_values));
}


bool Frequency_Table::is_in_range_percentile(int p)
{
  return (p >= 0 && p <= 100);
}


// Accepts a value between 0 and 100 to use as the percentile.
// Returns the data value at that index.
float Frequency_Table::get_percentile(int p)
{
  float percentile = -1;

  if (is_in_range_percentile(p))
  {
    percentile = (static_cast<float>(p) / 100);
    float percentile_index = percentile * (number_of_values + 1);

    if (is_an_integer(percentile_index))
    {
      percentile = data_values[percentile_index - 1];
    }
    else
    {
      percentile_index = floor(percentile_index);
      percentile = (data_values[percentile_index -1] + data_values[percentile_index]) / 2;
    }
  }
  else
  {
    std::cerr << "Please select a percentile value between 0 and 100." << std::endl;
  }

  return percentile;
}


// Accepts a data value.
// Returns the percentile of that value.
int get_data_at_percentile(float d)
{
  int percentile = -1;


  return percentile;
}


// Accepts a value 1, 2, or 3 to represent the quartile it is looking for.
// Returns the data value element at the location of the quartile index.
float Frequency_Table::get_quartile(Quartile q)
{
  float quartile = 0.0;

  switch(q)
  {
    case Quartile::first:
      quartile = get_percentile(25);
      break;

    case Quartile::second:
      quartile = get_median(data_values);
      break;

    case Quartile::third:
      quartile = get_percentile(75);
      break;

    default:
      std::cerr << "Please select a valid quartile value." << std::endl;
  }

  return quartile;
}


// Gets the interquartile range.
float Frequency_Table::get_IQR()
{
  float iqr = get_quartile_3() - get_quartile_1();

  return iqr;
}


void Frequency_Table::find_quartile(Quartile q)
{
  switch(q)
  {
    case Quartile::first:
      quartile_1 = get_quartile(Quartile::first);
      break;

    case Quartile::second:
      quartile_2 = get_quartile(Quartile::second);
      break;

    case Quartile::third:
      quartile_3 = get_quartile(Quartile::third);
      break;

    default:
      std::cerr << "Please select a valid quartile value." << std::endl;
  }
}


float Frequency_Table::get_quartile_1()
{
  return quartile_1;
}

float Frequency_Table::get_quartile_2()
{
  return quartile_2;
}

float Frequency_Table::get_quartile_3()
{
    return quartile_3;
}

void Frequency_Table::find_outlier_threshhold_high()
{
  outlier_threshhold_high = quartile_3 + (iqr * 1.5);
}

void Frequency_Table::find_outlier_threshhold_low()
{
  outlier_threshhold_low = quartile_1 - (iqr * 1.5);
}

float Frequency_Table::get_outlier_threshhold_high()
{
  return outlier_threshhold_high;
}

float Frequency_Table::get_outlier_threshhold_low()
{
  return outlier_threshhold_low;
}

float Frequency_Table::find_variance()
{
  float variance = 0.0;

  if(!is_grouped)
  {
    variance = find_variance_items();
  }
  else
  {
    variance = find_variance_intervals();
  }

  return variance;
}

float Frequency_Table::find_variance_items()
{
  float deviation = 0.0;
  float variance = 0.0;

  for (Frequency_Row fr : rows)
  {
    deviation = (fr.get_data_value() - mean);
    variance += ((deviation * deviation) * fr.get_frequency());
  }

  return variance;
}

float Frequency_Table::find_variance_intervals()
{
  float deviation = 0.0;
  float variance = 0.0;

  for (Data_Bin db : bins)
  {
    deviation = (db.get_bin_midpoint() - mean);
    variance += ((deviation * deviation) * db.get_bin_frequency());
  }

  return variance;
}

void Frequency_Table::find_standard_deviation()
{
  float variance = find_variance();

  variance /= (number_of_values - 1);

  standard_deviation = sqrt(variance);
}

float Frequency_Table::get_standard_deviation()
{
  return standard_deviation;
}

void Frequency_Table::find_z_score()
{
  float z = 0;

  for (int i = 0; i < number_of_rows; i++)
  {
    z = ((rows[i].get_data_value() - mean) / standard_deviation);
    rows[i].set_z_score(z);
  }
}


