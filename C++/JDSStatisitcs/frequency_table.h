/*
 * frequencyTable.h
 *
 *  Created on: Oct 5, 2020
 *      Author: jonesy
 */

#ifndef FREQUENCY_TABLE_H_
#define FREQUENCY_TABLE_H_

#include <vector>
#include <string>
#include "frequency_row.h"
#include "data_bin.h"
#include "JDSstdlib.h"

enum class Quartile{first = 1, second = 2, third = 3};
const float interval_start_offset_tenths = 0.5;
const float interval_start_offset_hundredths = 0.05;
const float interval_start_offset_thousandths = 0.005;

class Frequency_Table
{
  public:
    Frequency_Table();
    Frequency_Table(std::vector<float>);
    void init_table();
    std::vector<Frequency_Row> get_rows();
    int get_number_of_values();
    int get_number_of_rows();
    bool get_is_grouped();
    void set_is_grouped(bool);
    float get_interval();
    int get_size_of_interval();
    std::vector<float> get_interval_boundaries();
    std::vector<Data_Bin> get_data_bins();
    int get_number_of_intervals();
    void set_number_of_intervals(int);
    void set_number_of_intervals_default();
    void set_up_intervals();
    float get_interval_start_offset();
    void set_interval_start_offset(float);
    float get_interval_start_value();
    float get_interval_end_value();
    float get_median(std::vector<float>);
    float get_mean();
    std::vector<float> get_mode();
    float get_quartile(Quartile);
    float get_percentile(int);
    int get_data_at_percentile(float);
    float get_min_value();
    float get_max_value();
    float get_IQR();
    float get_quartile_1();
    float get_quartile_2();
    float get_quartile_3();
    float get_outlier_threshhold_high();
    float get_outlier_threshhold_low();
    float get_standard_deviation();

  private:
    // Data.
    std::vector<float> data_values;
    std::vector<Frequency_Row> rows;
    std::vector<Data_Bin> bins;
    std::vector<float> interval_boundaries;
    std::vector<int> data_bins;
    int number_of_values;
    int number_of_rows;
    bool is_grouped;
    int size_of_interval;
    int number_of_intervals;
    float interval_start_offset;
    float interval_start_value;
    float interval_end_value;
    float median;
    float mean;
    std::vector<float> mode;
    float iqr;
    float quartile_1;
    float quartile_2;
    float quartile_3;
    float outlier_threshhold_low;
    float outlier_threshhold_high;
    float min_value;
    float max_value;
    float standard_deviation;

    // Functions.
    void create_frequency_rows();
    void create_row(int);
    bool is_new_table_value(int);
    bool is_in_range_percentile(int);
    void increment_frequency();
    void find_interval_start_and_end();
    void find_size_of_interval();
    void find_interval_boundaries();
    bool is_within_interval(int, int);
    void init_data_bins();
    void create_data_bins();
    float find_median(std::vector<float>);
    void find_mean();
    float find_mean_items();
    float find_mean_intervals();
    void find_mode();
    int get_max_frequency();
    void collect_mode_values(int);
    void find_node_str();
    void find_IQR();
    void find_min_value();
    void find_max_value();
    void find_frequency();
    void find_relative_frequency();
    void find_cumulative_relative_frequency();
    void find_percentile(int);
    void find_quartile(Quartile);
    void find_outlier_threshhold_high();
    void find_outlier_threshhold_low();
    float find_variance();
    float find_variance_items();
    float find_variance_intervals();
    void find_standard_deviation();
    void find_z_score();
    void find_z_score_items();
    void find_z_score_intervals();
};

#endif /* FREQUENCY_TABLE_H_ */
