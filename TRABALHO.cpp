/*	
	- Lucas Neves Sáber Gabriel
*/
#include <iostream>
#include <locale.h>
#include <fstream> //Arquivos
#include <cstring> //Usado para comparar o nome

using namespace std;

const string ARQUIVOP = "dados.txt";

struct registros{
	int regt;
};
registros tam;
struct pessoa {
	char nome[20];
	int idade;
	float peso;
	float altura;
	char objetivo[20];
	float IMC;
};
pessoa v;

fstream arquivo;

string mais(int k){
	string op;
	if (k==1){
		do {
			cout <<endl<<"Deseja inserir outra pessoa? [S] ou [N]: ";
			cin >> op;
			cout << endl;
		} while (op != "S" and op != "N");
	} else if (k==2){
		do {
			cout <<"Deseja buscar outro nome? [S] ou [N]: ";
			cin >> op;
			cout << endl;
		} while (op != "S" and op != "N");
	} else if (k==3){
		do {
			cout <<"Deseja calcular IMC de outra pessoa? [S] ou [N]: ";
			cin >> op;
			cout << endl;
		} while (op != "S" and op != "N");
	} else if(k==4){
		do {
			cout <<"Deseja alterar dados de outra pessoa? [S] ou [N]: ";
			cin >> op;
			cout << endl;
		} while (op != "S" and op != "N");
	}
	return op;
}
void peso(float IMC){
// De acordo com o calculo do IMC será informado a classificação da pessoa
	if (IMC < 18.5){
		cout << " - Magreza"<<endl<<endl;
	} else if(IMC >= 18.5 and IMC < 24.9){
		cout << " - Normal"<<endl<<endl;
	} else if(IMC >= 24.9 and IMC < 30){
		cout << " - Sobrepeso"<<endl<<endl;
	} else if(IMC >= 30 and IMC < 39.9) {
		cout << " - Obesidade"<<endl<<endl;
	} else {
		cout << " - Obesidade Grave"<<endl<<endl;
	}
}
void atualiza_reg(){
	arquivo.open(ARQUIVOP.c_str(), ios::binary | ios::in | ios::out);
	arquivo.seekp(0, ios::beg);
	arquivo.write((const char*) &tam, sizeof(registros));
	arquivo.close();
}
void colocar(int tamanho){
	arquivo.open(ARQUIVOP.c_str(), ios::binary | ios::in | ios::out);
	arquivo.seekp(tamanho, ios::beg);
	arquivo.write((const char*) &v, sizeof(pessoa));
	arquivo.close();
}
void inserir(){
	string op= "S";
	int i=0;
	
	while (i < 100 and op=="S"){
		
		cout << "Digite o nome: "; // Ex: Ana Clara
		cin.ignore();
		cin.getline(v.nome, 20);
		
		cout << "Digite a idade: "; // Ex: 25
		cin >> v.idade;
		
		cout << "Digite o peso: "; // Ex: 65.7
		cin >> v.peso;
		
		cout << "Digite a altura: "; // Ex: 1.75
		cin >> v.altura;
		
		cout << "Digite o objetivo: "; // Ex: Emagrecimento, Crescer...
		cin.ignore();
		cin.getline(v.objetivo, 20);
		
		v.IMC= 0; // Será calculado depois
		
		long int tamanho= sizeof(registros) + (sizeof(pessoa)*tam.regt);
		colocar(tamanho);
		
		tam.regt++;
		atualiza_reg();
		
		op= mais(1);
		
		if (op=="S"){
			i++;
		}
	}
	arquivo.close();
}
void imprimir(){
	fstream arquivo(ARQUIVOP.c_str(), ios::in);
	
	if (arquivo) {
		int cont= 0;
		
		while (cont < tam.regt){
			
			arquivo.seekg((cont*sizeof(pessoa)) + sizeof(registros));
			arquivo.read((char*)&v, sizeof(pessoa));
			
			cout << "INFORMAÇÕES:" <<endl;
			cout << "Nome: " << v.nome <<endl 
				 << "Idade: " << v.idade<<endl 
				 << "Peso: " << v.peso <<endl
				 << "Altura: " << v.altura <<endl
				 << "Objetivo: " << v.objetivo <<endl
				 << "IMC: ";
			if (v.IMC==0){
				cout << "Não calculado" <<endl<<endl;
			} else {
				cout << v.IMC;
				peso(v.IMC);
			}
			cont++;
		}
		if (tam.regt==0){
			cout <<"Insira dados!"<<endl<<endl;
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
void buscar(){
	arquivo.open(ARQUIVOP.c_str(), ios::in);
	
	if (arquivo){
		char buscar[20];
		string op="S";
		
		while (op=="S"){
			int i=0;
			int posicao= -1;
			cout <<"Qual nome que deseja buscar? ";
			cin.ignore();
			cin.getline(buscar, 20);
			
			while (i < tam.regt and posicao == -1){
				
			arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
			arquivo.read((char*)&v, sizeof(pessoa));
			
				if (strcmp(buscar, v.nome)== 0){
					posicao= i;
					cout <<endl<< "INFORMAÇÕES:" <<endl;
					cout << "Nome: " << v.nome <<endl 
						 << "Idade: " << v.idade<<endl 
						 << "Peso: " << v.peso <<endl
						 << "Altura: " << v.altura <<endl
						 << "Objetivo: " << v.objetivo <<endl
						 << "IMC: ";
					if (v.IMC==0){
						cout << "Não calculado" <<endl<<endl;
					} else {
						cout << v.IMC;
						peso(v.IMC);
					}
				}
				i++;
			}
			if (posicao == -1) {
				cout << "Nome não encontrado!" << endl<<endl;
			}
			op= mais(2);
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
pessoa ler(int pos){
	arquivo.open(ARQUIVOP.c_str(), ios::in);
	pessoa lendo;
	arquivo.seekg(pos, ios::beg);
	arquivo.read((char*) &lendo, sizeof(pessoa));
	arquivo.close();
	
	return lendo;
}
void excluir(){
	fstream arquivo(ARQUIVOP.c_str());
	
	if (arquivo){
		char buscar[20];
		string op="S";
		int i=0;
		int posicao= -1;
		
		cout << "Qual nome que deseja excluir? ";
		cin.ignore();
		cin.getline(buscar, 20);
		
		while (i < tam.regt and posicao == -1){
			
			arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
			arquivo.read((char*)&v, sizeof(pessoa));
			if (strcmp(buscar, v.nome)== 0){
				posicao= i;
			}
			i++;
		}
		int pos, aux;
		while (posicao < tam.regt and posicao != -1){
			
			pos= (posicao*sizeof(pessoa)) + sizeof(registros);
			aux= pos + sizeof(pessoa);
			v= ler(aux);
			colocar(pos);
			posicao++;
		}
		if (posicao==-1){
			cout << "Nome não encontrado!" <<endl<<endl;
		} else {
			cout << "Dados excluidos!" <<endl<<endl;
			tam.regt--;
			atualiza_reg();
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
void ordenar(){
// Ordernação feita pelo Selection Sort
	arquivo.open(ARQUIVOP.c_str(), ios::out | ios::in);
	
	if (arquivo){
		if (tam.regt > 0){
			pessoa menor;
			int k;
			for (int i=0; i < tam.regt; i++){
				
				arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
				arquivo.read((char*)&v, sizeof(pessoa));
				menor= v;
				k= i;
				
				for (int j=i+1; j < tam.regt; j++){
					
					arquivo.seekg((j*sizeof(pessoa)) + sizeof(registros));
					arquivo.read((char*)&v, sizeof(pessoa));
					
					if (strcmp(v.nome, menor.nome)<0){
						
						arquivo.seekg((j*sizeof(pessoa)) + sizeof(registros));
						arquivo.read((char*)&v, sizeof(pessoa));
						menor= v;
						k= j;
					}
				}
				pessoa aux;
				arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
				arquivo.read((char*)&v, sizeof(pessoa));
				aux= v;
				
				arquivo.seekg((k*sizeof(pessoa)) + sizeof(registros));
				arquivo.write((const char*) &v, sizeof(pessoa));
				v= menor;
				
				arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
				arquivo.write((const char*) &v, sizeof(pessoa));
				menor=aux;
				
			}
			cout << "Dados ordenados!"<<endl<<endl;
		} else{
			cout <<"Insira dados!"<<endl<<endl;
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
void IMC(){
// IMC é um parâmetro utilizado para calcular o peso ideal de cada pessoa
	arquivo.open(ARQUIVOP.c_str(), ios::out | ios::in);
	
	if (arquivo){
		char trocar[20];
		string op= "S";
		
		while (op=="S"){
			int i= 0;
			int posicao=-1;
			
			cout << "Qual nome da pessoa que deseja calcular o IMC? ";
			cin.ignore();
			cin.getline(trocar, 20);
			
			while (i < tam.regt and posicao == -1){
				
				arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
				arquivo.read((char*)&v, sizeof(pessoa));
				
				if (strcmp(trocar, v.nome)==0){
					posicao= i;
					
					arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
					v.IMC= v.peso/(v.altura*v.altura);
					arquivo.write((char*) &v, sizeof(pessoa));
					
					cout << "Calculado com sucesso!" <<endl<<endl;
				}
				i++;
			}
			if (posicao == -1){
				cout <<"Nome não encontrado!" <<endl<<endl;
			}
			op= mais(3);
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
void alterar(){
	arquivo.open(ARQUIVOP.c_str(), ios::in | ios::out);
	
	if (arquivo){
		char alterar[20];
		string op= "S";
		
		while (op=="S"){
			int i= 0;
			int posicao=-1;
			
			cout << "Qual nome da pessoa que deseja alterar os dados? ";
			cin.ignore();
			cin.getline(alterar, 20);
			
			while (i < tam.regt and posicao == -1){
				
				arquivo.seekg((i*sizeof(pessoa)) + sizeof(registros));
				arquivo.read((char*)&v, sizeof(pessoa));
				
				if (strcmp(alterar, v.nome)==0){
					posicao= i;
					
					cout << "Digite o nome: ";
					cin.getline(v.nome, 20);
					
					cout << "Digite a idade: ";
					cin >> v.idade;
							
					cout << "Digite o peso: ";
					cin >> v.peso;
							
					cout << "Digite a altura: ";
					cin >> v.altura;
							
					cout << "Digite o objetivo: ";
					cin.ignore();
					cin.getline(v.objetivo, 20);
							
					v.IMC= 0;
							
					arquivo.seekp(sizeof(registros) + (sizeof(pessoa)*i));
					arquivo.write((const char*) &v, sizeof(pessoa));
					
					cout <<endl<< "Dados alterados!" <<endl<<endl;
				}
				i++;
			}
			if (posicao == -1){
				cout <<"Nome não encontrado!" <<endl<<endl;
			}
			op= mais(4);
		}
	} else {
		cout << "Não existe arquivo!" <<endl;
	}
	arquivo.close();
}
void menu (){
	char opcao;
		do {
			cout << "------------------" <<endl;
			cout << "       MENU        " <<endl;
			cout << "------------------" <<endl;
			cout << "   1. Inserir" <<endl;
			cout << "   2. Imprimir" <<endl;
			cout << "   3. Buscar" <<endl;
			cout << "   4. Excluir" <<endl;
			cout << "   5. Ordenar" <<endl;
			cout << "   6. Calcular IMC" <<endl;
			cout << "   7. Alterar" <<endl;
			cout << "   8. Sair" <<endl;
			cout << "------------------" <<endl;
			cout << "Digite a opção: ";
			cin >> opcao;
			cout << endl;
			
			switch (opcao) {
				case '1':
					inserir();
					break;
				case '2':
					imprimir();
					break;
				case '3':
					buscar();
					break;
				case '4':
					excluir();
					break;
				case '5':
					ordenar();
					break;
				case '6':
					IMC();
					break;
				case '7':
					alterar();
					break;
				case '8':
					break;
				default: cout <<"Opção invalida!"<<endl;
			}
		} while (opcao != '8');
}

int main (){
	arquivo.open(ARQUIVOP.c_str());
	
	if (arquivo){
		arquivo.read((char*) &tam, sizeof(registros));
		arquivo.close();
	} else {
		ofstream arquivo(ARQUIVOP.c_str(), ios::out);
	}
	
	menu();
	arquivo.close();
	return 0;
}
