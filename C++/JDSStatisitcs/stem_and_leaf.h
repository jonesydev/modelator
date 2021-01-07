/*
 * stemAndLeafPlot.hpp
 *
 *  Created on: Oct 3, 2020
 *      Author: jonesy
 */

#ifndef STEM_AND_LEAF_PLOT_H_
#define STEM_AND_LEAF_PLOT_H_

#include <vector>

class Stem_and_Leaf
{
  public:
    Stem_and_Leaf();
    Stem_and_Leaf(std::vector<float>);
    //std::vector<int> get_stems();
    std::vector<std::vector<int>> get_stems_and_leaves();
    void set_stems_and_leaves(std::vector<std::vector<int>>);
    //std::vector<int> get_leaves_stem();
    int get_number_of_values();
    int get_number_of_rows();
    std::vector<int> get_leaves_of_stem(int);
    void init_table();

  private:
    // Data.
    std::vector<float> data_values;
    std::vector<std::vector<int>> stems_and_leaves;
    int number_of_values;
    int number_of_rows;

    // Functions.
    //void separate_stems_and_leaves(int);
    int find_stem(int);
    int find_leaf(int);
    void create_row(int, int);
};



#endif /* STEM_AND_LEAF_H_ */
