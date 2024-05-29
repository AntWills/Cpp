#ifndef MENU_H
#define MENU_H

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

  void opcoes_menu();
  void informacoes_teclado();

  static void coluna_linha(int,int);
};

Menu::Menu() {
  pose_vector = 0;
  meno_oculto = false;
  informacoes_oculta = false;
}

void Menu::click_keyboard(char a_d_m){
  if(a_d_m == 'a'){
    if(pose_vector != 0){
      pose_vector--;
    }
    return;
  }

  if(a_d_m == 'd'){
    if(pose_vector != (size_vector - 1)){
      pose_vector++;
    }
    return;
  }

  if(a_d_m == 'm'){
    meno_oculto = !meno_oculto;
    return;
  }

  if(a_d_m == 'i'){
    informacoes_oculta = !informacoes_oculta;
  }
}

void Menu::opcoes_menu(){
  if(!meno_oculto){
    return;
  }

  std::cout << "\nbbbbb\n\n";

  std::cout << "aaaaa\n";
  std::cout << "aaaaa\n";
  std::cout << "aaaaa\n";
  std::cout << "aaaaa\n";
}

void Menu::coluna_linha(int x,int y){
  std::cout << "\033[" << y << ";" << x << "H";
  std::cout << "(" << x << ","<< y <<")";
}


void Menu::informacoes_teclado(){
  if(!informacoes_oculta){
    return;
  }

  coluna_linha(20, 4);
  std::cout << "I - Abrir informacoes do teclado.\n";
  coluna_linha(20, 5);
  std::cout << "A - avancar para esquerda.\n";
  coluna_linha(20, 6);
  std::cout << "D - avancar para direita.\n";
  coluna_linha(20, 7);
  std::cout << "M - meno.\n";
}


#endif