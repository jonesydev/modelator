/*
 * frequencyTable.hpp
 *
 *  Created on: Oct 1, 2020
 *      Author: jonesy
 */

#ifndef FREQUENCY_ROW_H_
#define FREQUENCY_ROW_H_

#include <vector>
#include <string>

class Frequency_Row
{
  public:
	  Frequency_Row();

	  Frequency_Row(float data_value,
			            int frequency,
				          float relative_frequency,
				          float cumulative_relative_frequency,
				          bool is_grouped,
				          float interval);

	  Frequency_Row(std::string &data_value,
				          int frequency=0,
				          float relative_frequency=0,
				          float cumulative_relative_frequency=0);

	  void set_data_value(float);
	  void set_data_value(std::string&);
	  float get_data_value();
	  std::string get_data_value_string();
	  int get_frequency();
	  void set_frequency(int);
	  float get_relative_frequency();
	  void set_relative_frequency(float);
    float get_cumulative_relative_frequency();
    void set_cumulative_relative_frequency(float);
    void increment_frequency();
    void set_z_score(float);
    float get_z_score();


  private:
	  float data_value;
	  std::string data_value_str;
	  int frequency;
	  float relative_frequency;
	  float cumulative_relative_frequency;
	  bool is_grouped;
	  float interval;
	  float z_score;
};


#endif /* FREQUENCY_ROW_H_ */
