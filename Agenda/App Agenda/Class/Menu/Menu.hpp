#ifndef MENU_H
#define MENU_H

#include "../ViewerData/ViewerData.hpp"

class Menu{
 private:
  int pose_vector, size_vector;
  char tecla;

  bool meno_oculto;
  bool informacoes_oculta;

  
 public:
  Menu();

  void set_size_vector(int size) { size_vector = size; }
  void click_keyboard(char);

  int get_pose_vector() { return pose_vector; }
  char get_key() { return tecla; }

  void opcoes_menu();
  void informacoes_teclado();

  
};

Menu::Menu() {
  pose_vector = 0;
  meno_oculto = false;
  informacoes_oculta = false;
}

void Menu::click_keyboard(char a_d_m_i){
  tecla = a_d_m_i;

  if(a_d_m_i == 'a'){
    if(pose_vector != 0){
      pose_vector--;
    }
    return;
  }

  if(a_d_m_i == 'd'){
    if(pose_vector != (size_vector - 1)){
      pose_vector++;
    }
    return;
  }

  if(a_d_m_i == 'm'){
    meno_oculto = !meno_oculto;
    return;
  }

  if(a_d_m_i == 'e'){
    informacoes_oculta = !informacoes_oculta;
  }
}

void Menu::opcoes_menu(){
  if(!meno_oculto){
    return;
  }

  Viewer::coluna_linha(0, 13);
  std::cout << "\n#  Menu  #\n\n";

  std::cout << "1. Mostrar mais informacoes(teste).\n";
  std::cout << "2. Agendar para uma data(teste).\n";
  std::cout << "3. Configuracoes(teste)\n";
  std::cout << "0. Encerrar.\n";
}


void Menu::informacoes_teclado(){
  if(!informacoes_oculta){
    return;
  }

  int X = 37, Y = 14;

  Viewer::coluna_linha(X, Y);
  std::cout << "| E - Exibir informacoes do teclado.\n";
  Viewer::coluna_linha(X, Y + 1);
  std::cout << "| A - Avancar para esquerda.\n";
  Viewer::coluna_linha(X, Y + 2);
  std::cout << "| D - Avancar para direita.\n";
  Viewer::coluna_linha(X, Y + 3);
  std::cout << "| M - Menu.\n";
}


#endif