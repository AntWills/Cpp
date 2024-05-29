#include <iostream>
#include <vector>

#include "Class/Date/Date.hpp"
#include "Class/ViewerData/ViewerData.hpp"

int main() {
  std::vector<std::vector<Date>> year;

  for (int i = 0; i < 12; i++) {
    std::vector<Date> month;
    year.push_back(month);
    for (int j = 0; j < Date::quant_day_month(i + 1); j++) {
      year.at(i).push_back(Date(j + 1, i + 1, 2024));
    }
  }

  for (int i = 0; i < 12; i++) {
    std::cout << "\n\t\tMes: " << Date::get_name_month(i) << "\n";
    Viewer::viewer_month(year.at(i));
  }
  return 0;
}