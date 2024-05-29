#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>

class Date {
 private:
  int day, month, year, day_week;
  bool data_comemorativa;

  std::string tipo_comemoracao;
  std::vector <std::string> name_day_week = 
  { 
    "Domingo", "Segunda-feira", "Terca-feira", "Quarta-feira",
    "Quinta-feira", "Sexta-feira", "Sabado"
  };

  static bool check_day(int, int, int);
  void org_date();
  int seek_day_week();

 public:
  Date();
  Date(int, int, int);
  Date(int, int, int, std::string);
  Date(int, int, int, int);
  Date(int, int, int, int, std::string);

  std::string to_strin();

  void print_day();
  std::string sprint_day();

  std::string get_tipoFeriado() { return tipo_comemoracao; }
  int get_day() { return day; }
  int get_month() { return month; }
  int get_year() { return year; }
  bool get_data_comemorativa() { return data_comemorativa; }
  int get_day_week() { return day_week; }
  std::string get_name_day_weel() { return name_day_week.at(day_week); }

  void set_data_comemorativa(bool dc) { data_comemorativa = dc; }
  void set_comemoracao(std::string cmc) { tipo_comemoracao = cmc; }

  bool operator==(Date&);
  Date& operator++();
  Date& operator++(int);

  static int quant_day_month(int);
  static bool check_date(int, int);
  static bool check_date(Date&);
};

Date::Date() {
  day = 1;
  month = 1;
  year = 1;
  data_comemorativa = false;
  tipo_comemoracao = "";
}

Date::Date(int d, int m, int y)
    : day(d), month(m), year(y), data_comemorativa(false) {
  org_date();
  day_week = seek_day_week();
}

Date::Date(int d, int m, int y, std::string t)
    : day(d), month(m), year(y), tipo_comemoracao(t) {
  data_comemorativa = true;
  org_date();
  day_week = seek_day_week();
}

Date::Date(int d, int m, int y, int dw)
    : day(d), month(m), year(y), day_week(dw), data_comemorativa(false) {
  org_date();
}

Date::Date(int d, int m, int y, int dw, std::string t)
     : day(d), month(m), year(y), day_week(dw) ,tipo_comemoracao(t) {
  data_comemorativa = true;
  org_date();
}

void Date::org_date() {
  while (this->day > Date::quant_day_month(this->month)) {
    this->day -= Date::quant_day_month(this->month);
    this->month++;
  }

  while (this->month > 12) {
    this->month -= 12;
    this->year++;
  }
}

int Date::seek_day_week(){
  int conta_day = 0;

  for(int auxi = 1; auxi != this->month; auxi++)
    conta_day += quant_day_month(auxi);
  
  return (conta_day + this->day) % 7;
}

std::string Date::to_strin() {
  std::string sday = std::to_string(day);
  if (day < 10)
    sday.insert(0, "0");

  std::string smonth = std::to_string(month);
  if (month < 10)
    smonth.insert(0, "0");

  std::string syear = std::to_string(year);

  return sday + "/" + smonth + "/" + syear;
}

void Date::print_day() {
  if (day < 10)
    std::cout << "0";
  if (data_comemorativa)
    std::cout << day << "* ";
  else
    std::cout << day << "  ";
}

std::string Date::sprint_day() {
  std::string sday = std::to_string(day);

  if (day < 10)
    sday.insert(0, "0");

  if (data_comemorativa)
    sday += "* ";
  else
    sday += "  ";

  return sday;
}

bool Date::operator==(Date& date) {
  if (this->day == date.day)
    if (this->month == date.month)
      if (this->year == date.year)
        return true;
  return false;
}

Date& Date::operator++() {
  this->day++;

  org_date();

  return *this;
}

Date& Date::operator++(int) {
  Date auxi(*this);
  ++(*this);
  return auxi;
}

bool Date::check_day(int inicio, int fim, int day) {
  if (day >= inicio && day <= fim)
    return true;
  return false;
}

int Date::quant_day_month(int month) {
  if (month == 1 || month == 3 || month == 5 || month == 7) {
    return 31;
  } else if (month == 8 || month == 10 || month == 12)
    return 31;

  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;

  if (month == 2)
    return 29;

  return 0;
}

bool Date::check_date(int day, int month) {
  return check_day(1, quant_day_month(month), day);
}

bool Date::check_date(Date& date) {
  return check_date(date.get_day(), date.get_month());
}

#endif