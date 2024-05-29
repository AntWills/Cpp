#include <conio.h>
#include <iostream>
#include <vector>
#include "Class/Menu/Menu.hpp"

int main() {
  system("clear");
  std::vector<std::string> nomes = {"antonio wills", "acelio herreiras",
                                    "jonas da silva", "wilma conceicao"};

  Menu meno;
  do{
    
    meno.set_size_vector(nomes.size());

    std::cout << "\nNomes: " << nomes.at(meno.get_pose_vector()) << "\n";
    meno.opcoes_menu();
    meno.informacoes_teclado();

    meno.click_keyboard(_getch());
    system("clear");
  }while(true);

  return 0;
}