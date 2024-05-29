#ifndef VIEWERDATA_H
#define VIEWERDATA_H

#include <iostream>
#include <vector>
#include "../Color/Color.hpp"
#include "../Date/Date.hpp"

class Viewer {
 private:
  static void divisor();
  static void days_week();
  static void print_day(Date&);

 public:
  static void viewer_month(std::vector<Date>&);
  static void viewer_national_holiday(std::vector<Date>&);

  static void coluna_linha(int,int);
};

void Viewer::divisor() {
  std::cout << "\n-------------------------------------------\n";
}

void Viewer::days_week() {
  std::string name_days[] = {"Do", "Se", "Te", "Qu", "Qu", "Se", "Sa"};
  for (int i = 0; i < 7; i++)
    std::cout << " " << name_days[i] << "   ";
}

void Viewer::print_day(Date& date) {
  if (date.get_data_comemorativa()) {
    std::cout << RED << " " + date.sprint_day() + "|" << RESET;
    return;
  }

  if (date.get_day_week() == 0 || date.get_day_week() == 6) {
    std::cout << BLUE << " " + date.sprint_day() + "|" << RESET;
    return;
  }

  std::cout << " " << date.sprint_day() << "|";
}

void Viewer::viewer_month(std::vector<Date>& month) {
  divisor();
  Viewer::days_week();
  divisor();

  int day_week = month.at(0).get_day_week();
  int month_size = month.size();
  int conta = 0;
  for (int i = 0; i < day_week; i++) {
    std::cout << "     |";
    conta++;
  }

  for (int i = 0; i < month_size; i++) {
    print_day(month.at(i));
    conta++;
    if (conta == 7 && i != (month_size - 1)) {
      conta = 0;
      std::cout << std::endl;
    }
  }

  std::cout << std::endl;
}

void Viewer::viewer_national_holiday(std::vector<Date>& month){
  int month_size = month.size();
  int Y = 7;

  for (int i = 0; i < month_size; i++) {
    if(month.at(i).get_data_comemorativa()){
      coluna_linha(45, Y);
      std::cout << RED << "* " << month.at(i).get_tipoFeriado() << RESET;
      Y++;
    }
  }
}

void Viewer::coluna_linha(int x,int y){
  std::cout << "\033[" << y << ";" << x << "H";
  //std::cout << "(" << x << ","<< y <<")";
}

#endif