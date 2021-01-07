/*
 * data_bin.h
 *
 *  Created on: Oct 28, 2020
 *      Author: jonesy
 */

#ifndef DATA_BIN_H_
#define DATA_BIN_H_

#include <vector>
//#include "JDSstdlib.h"

class Data_Bin
{
  public:
    // Constructors.
    Data_Bin();
    Data_Bin(float, float);

    // Functions.
    float get_bound_lower();
    float get_bound_upper();
    float get_bin_midpoint();
    int get_bin_frequency();
    void add_to_bin_frequency(int);
    void set_bound_lower(float);
    void set_bound_upper(float);
    void set_bin_frequency(int);
    void find_bin_midpoint();

  private:
    // Data.
    float bound_lower;
    float bound_upper;
    float bin_midpoint;
    int bin_frequency;
};

#endif /* DATA_BIN_H_ */
