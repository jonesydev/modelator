/*
 * stats_calc.cpp
 *
 *  Created on: Jan 29, 2021
 *      Author: jonesy
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <nlohmann/json.hpp>
#include "frequency_row.h"
#include "frequency_table.h"
#include "data_bin.h"
#include "stem_and_leaf.h"
#include "JDSstdlib.h"

using json = nlohmann::json;

int main(int argc, char *argv[])
//int main()
{
  //std::string input = "4,5,2,2,7,7,7,9,3,6";
  std::string input = argv[1];
  int input_length = input.length() + 1;
  char input_chars[input_length];
  std::vector<float> data_set = {};
  std::vector<float> data_values = {};
  std::vector<float> frequencies = {};
  std::vector<float> relative_frequencies = {};
  std::vector<float> cumulative_relative_frequencies = {};
  std::vector<float> z_scores = {};


  std::strcpy(input_chars, input.c_str());
  std::string temp_string = "";

  //std::cout << input << std::endl;

  for (int i = 0; i < input_length; i++)
  {
    //std::cout << input_chars[i] << std::endl;

    if ((input_chars[i] != ',') || i == input_length - 1)
    //if ((isdigit(input_chars[i])) || i == input_length - 1)
    {
      temp_string.push_back(input_chars[i]);

      if (i == input_length - 1)
      {
        data_set.push_back(std::stof(temp_string));
        temp_string = "";
      }
    }
    else
    {
      //std::cout << temp_string << std::endl;
      data_set.push_back(std::stof(temp_string));
      temp_string = "";
    }
  }

  //float src[input.length()] = {};

  //src = std::atof(input);



  //for (int i = 1; i < argc; i++)
  //{
  //  data_set.push_back(std::atof(argv[1]));
  //}

  Frequency_Table ft = {data_set};
  //std::vector<Frequency_Row> fr_vec = {};
  json json_ft;

  ft.init_table();

  json_ft["minimum"] = ft.get_min_value();
  json_ft["maximum"] = ft.get_max_value();
  json_ft["mean"] = ft.get_mean();
  json_ft["median"] = ft.get_median(data_set);
  json_ft["standard_deviation"] = ft.get_standard_deviation();
  json_ft["mode"] = ft.get_mode();
  json_ft["sum"] = ft.get_sum();
  json_ft["range"] = ft.get_range();
  json_ft["count"] = ft.get_number_of_values();
  json_ft["variance"] = ft.get_variance();

  //std::cout << "JSON: " << json_ft << std::endl;

//  std::cout << "minimum:" << ft.get_min_value() << std::endl;
//  std::cout << "maximum:" << ft.get_max_value() << std::endl;
//  std::cout << "mean:" << ft.get_mean() << std::endl;
//  std::cout << "median:" << ft.get_median(data_set) << std::endl;
//  std::cout << "standard_deviation:" << ft.get_standard_deviation() << std::endl;
//  std::cout << "mode:";

//  if (size(ft.get_mode()) > 0)
//  {
//    std::vector<float> vec_mode = {};
//
//    for (float m : ft.get_mode())
//    {
//      //vec_mode.push_back(m);
//      std::cout << m << std::endl;
//    }
//  }
//  else
//  {
//    std::cout << "there was no mode in this data set" << std::endl;
//  }

  json_ft["percentile_25"] = ft.get_quartile(Quartile::first);
  json_ft["percentile_75"] = ft.get_quartile(Quartile::third);
  json_ft["iqr"] = ft.get_IQR();

  json_ft["percentile_10"] = ft.get_percentile(10);
  json_ft["percentile_20"] = ft.get_percentile(20);
  json_ft["percentile_30"] = ft.get_percentile(30);
  json_ft["percentile_40"] = ft.get_percentile(40);
  json_ft["percentile_60"] = ft.get_percentile(60);
  json_ft["percentile_70"] = ft.get_percentile(70);
  json_ft["percentile_80"] = ft.get_percentile(80);
  json_ft["percentile_90"] = ft.get_percentile(90);


//  std::cout << "percentile_25:" << ft.get_quartile(Quartile::first) << std::endl;
//  std::cout << "percentile_75:" << ft.get_quartile(Quartile::third) << std::endl;
//  std::cout << "IQR:" << ft.get_IQR() << std::endl;
//
//  std::cout << "z-score:" <<std::endl;

//  for (Frequency_Row fr : ft.get_rows())
//  {
//    fr_vec.push_back(fr);
//    std::cout << "data_value:" << fr.get_data_value() << ", " << "score:" << fr.get_z_score() << std::endl;
//  }


  for (Frequency_Row fr : ft.get_rows())
  {
    data_values.push_back(fr.get_data_value());
    frequencies.push_back(fr.get_frequency());
    relative_frequencies.push_back(fr.get_relative_frequency());
    cumulative_relative_frequencies.push_back(fr.get_cumulative_relative_frequency());
    z_scores.push_back(fr.get_z_score());
  }

  json_ft["data_values"] = data_values;
  json_ft["frequencies"] = frequencies;
  json_ft["relative_frequencies"] = relative_frequencies;
  json_ft["cumulative_relative_frequencies"] = cumulative_relative_frequencies;
  json_ft["z_scores"] = z_scores;

//  std::string dv = "data_values:";
//  int data_values_length = size(data_values);
//
//  for (int i = 0; i < data_values_length; i++)
//  {
//    if (i < data_values_length - 1)
//    {
//      std::strcat(dv, std::to_string(data_values[i]));
//    }
//    else
//    {
//      dv += dv;
//    }
//  }
//
//  std::cout << dv;

//  std::cout << "data_values:" << std::endl;
//
//  for (float d : data_values)
//  {
//    std::cout << d << std::endl;
//  }
//
//  std::cout << "frequencies:" << std::endl;
//
//  for (float f : frequencies)
//  {
//    std::cout << f << std::endl;
//  }
//
//  std::cout << "relative_frequencies:" << std::endl;
//
//  for (float rf : relative_frequencies)
//  {
//    std::cout << rf << std::endl;
//  }
//
//  std::cout << "cumulative_relative_frequencies:" << std::endl;
//
//  for (float crf : cumulative_relative_frequencies)
//  {
//    std::cout << crf << std::endl;
//  }

  std::cout << json_ft;

  return 0;
}

