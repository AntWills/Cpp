#ifndef APPAGENDA_H
#define APPAGENDA_H

#include <iostream>
#include <vector>
#include <conio.h>
#include "../Date/Date.hpp"
#include "../ViewerData/ViewerData.hpp"
#include "../Menu/Menu.hpp"

class AppAgenda {
 private:
  std::vector<std::vector<Date>> calendario;
  Menu menu;

 public:
  AppAgenda();
  ~AppAgenda() {}

  void start();
};

AppAgenda::AppAgenda() {
  for (int i = 0; i < 12; i++) {
    std::vector<Date> month;
    calendario.push_back(month);
    for (int j = 0; j < Date::quant_day_month(i+1); j++) {
      calendario.at(i).push_back(Date(j + 1, i + 1, 2024));
    }
  }
}

void AppAgenda::start() {
  system("clear");

  do{
    menu.set_size_vector(calendario.size());
    Viewer::coluna_linha(20,2);
    std::cout << Date::get_name_month(menu.get_pose_vector()) << "\n";
    Viewer::viewer_month(calendario.at(menu.get_pose_vector()));

    menu.opcoes_menu();
    menu.informacoes_teclado();
    Viewer::viewer_national_holiday(calendario.at(menu.get_pose_vector()));

    menu.click_keyboard(_getch());
    system("clear");
  }while(menu.get_key() != '0');
}

#endif