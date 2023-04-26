#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<sys/stat.h>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
struct MakeFile{
  std::string arquivo_Make;
  std::string arquivo_Orig;
  std::string arquivo_Targ;
  std::string argum;
  bool argum_def = false;
};

MakeFile setMake(void){
 MakeFile mk;

 std::cout << "Digite o Nome do Arquivo Make Com Extensao .Make: ";
 std::cin >> mk.arquivo_Make;

 std::cout << "Digite o Nome do Arquivo Target Sem Extensao: ";
 std::cin >> mk.arquivo_Targ;

 std::cout << "Digite \\n Para Deixao Sem Argumento: " << std::endl;

 std::cout << "Digite os Argumentos do g++  : ";
 std::cin >> mk.argum;
 
 if(std::cin.fail()){
   std::cin.clear();
   std::cin.ignore(10000,'\n');
 }else{
   mk.argum_def = true;
 }



 return mk;
}

class MakeFile_Control{
  private:
   std::string name = "Make_O_File(g++,make)";
   std::string author = "Deivid K.L";
   std::string version = "0.0.1";
  public:
   void init(void){
      system("clear");
      std::cout << "Projeto: " << std::setfill('.') 
	        << std::setw(10) << " " << name << std::endl;
      std::cout << "Author: " << std::setfill('.')
	        << std::setw(11) << " " << author << std::endl;
      std::cout << "Version: " << std::setfill('.')
	        << std::setw(10) << " " << version << std::endl;
      std::cout << std::endl;
   }
  void createMakeFile(void){

      MakeFile make = setMake();
      std::ofstream arquivo(make.arquivo_Make);

      if(arquivo.is_open()){
	arquivo << "CC  =  g++ \n";
	arquivo << "\n";
	if(make.argum_def == true){
	  arquivo << "CCFLGS = " << make.argum << "\n";
	}
	arquivo << "\n";
	arquivo << "TARGET = " << make.arquivo_Targ << "\n";
	arquivo << "\n";
	arquivo << "CLEAN_ELF = termux-elf-cleaner" << "\n";
	arquivo << "\n";
	arquivo << "all:$(TARGET)\n";
        arquivo << "$(TARGET):$(TARGET).cpp\n";
        if(make.argum_def == true){
		arquivo << "\t$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp\n";
	}
	arquivo << "\t$(CLEAN_ELF) $(TARGET)\n";
	arquivo << "\n";
	arquivo << "clean:\n\t$(RM) $(TARGET);\n";
	
	arquivo.close();
        
   	std::cout << "Arquivo " << make.arquivo_Targ << ": Criado Com Sucesso" << std::endl;

      }else{
	std::cout << "Arquivo " << make.arquivo_Make << ": Erro ao Criar Arquivo";
      }


  }
  void compileArquivo(void){
	init();
	std::string nome_Arq;
	std::cout << "Digite O Nome Do Arquivo.Make: ";
	std::cin >> nome_Arq;
	std::string buff_CMD = "make -f " + nome_Arq;
	const char* CMD = buff_CMD.c_str();
	system(CMD);
  }

  void createPastas_DR(void){
   system("clear");
   init();
   std::string Pasta_D = "Debug";
   std::string Pasta_R = "Release";

   int status_D = mkdir(Pasta_D.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

   if(status_D == 0){
        std::cout << "Pasta " << Pasta_D << ": Criada Com Sucesso" << std::endl;
   }else{
        std::cout << "Pasta " << Pasta_D << ": Erro Ao Criar" << std::endl;
   }

   int status_R = mkdir(Pasta_R.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

   if(status_R == 0){
        std::cout << "Pasta " << Pasta_R << ": Criada Com Sucesso" << std::endl;           }else{
        std::cout << "Pasta " << Pasta_R << ": Erro Ao Criar" << std::endl;
   }

  }
  void MoveArquivo(void){
      init();
      std::string buff_a;
      std::cout << "Digite o Nome do Arquivo Compilado: ";
      std::cin >> buff_a;
      const char* N_arquivo = buff_a.c_str();
      
      std::string D_debug = "Debug/";
      std::string buff_d = D_debug + N_arquivo;
      const char*  caminho_D = buff_d.c_str();

      std::string D_release = "Release/";
      std::string buff_r = D_release + N_arquivo;
      const char* caminho_R = buff_r.c_str();

      int opcao;

      std::cout << std::endl;
      std::cout << "1) Mover para Debug" << std::endl;
      std::cout << "2) Mover para Release" << std::endl;
      std::cout << "Digite: ";
      std::cin >> opcao;

      if(opcao == 1){
	 std::cout << "Movendo " << N_arquivo << " Para "  << D_debug << std::endl;
	 if(std::rename(N_arquivo,caminho_D) != 0){
	   std::perror("Erro Ao Mover o Arquivo");
	 }
      }
      else if(opcao == 2){
	 std::cout << "Movendo " << N_arquivo << " Para " << D_release << std::endl;
	 if(std::rename(N_arquivo,caminho_R) != 0){
	  std::perror("Erro Ao Mover o Arquivo");
	 }
      }
      else{
	 std::cout << "Opcao Invalida!" << std::endl;
      }
  }
  void ExecutaArquivo(){
     init();
     std::string cmd = "./";
     std::string arquivoC;
     std::string P_d;

     std::cout << "Digite o Nome do Compilado: ";
     std::cin >> arquivoC;

     std::cout << "Digite o Nome da Pasta: ";
     std::cin >> P_d;

     std::string buff_cmd = cmd + P_d + "/" + arquivoC;
     const char* CMD_Completo = buff_cmd.c_str();
     system(CMD_Completo);
  }
};
void Menu(){
   system("clear");
   MakeFile_Control MKC;
   MKC.init();
   int opc;
   std::cout << "Menu De Opcoes" << std::endl;
   std::cout << "1) Criar Arquivo Make" << std::endl;
   std::cout << "2) Executar arquivo Make" <<std::endl;
   std::cout << "3) Criar Pastas Debug e Release" << std::endl;
   std::cout << "4) Mover Programa Para Debug ou Release" << std::endl;
   std::cout << "5) Executar Programa Diretamente da Pasta" << std::endl;
   std::cout << "Digite: ";
   std::cin >> opc;
   if(opc == 1){
	MKC.createMakeFile();
   }
   else if(opc ==2){
	MKC.compileArquivo();
   }
   else if(opc == 3){
	MKC.createPastas_DR();
   }
   else if(opc == 4){
	MKC.MoveArquivo();
   }
   else if(opc == 5){
	MKC.ExecutaArquivo();
   }
   else{
     std::cout << "Opcao Invalida" << std::endl;
   }

  
}



int main(){
  Menu();
}
