// useUnityComCpp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "pch.h"
#include <iostream>
#include "../UnityComCpp/UnityCom.h"

void PrintOptions();

constexpr auto ARRAY_SIZE = 3;

int main()
{
	//float a = 3.2;
	//float b = 4.2;
	//float c = Add(a, b);
	//std::cout << c << std::endl;

	int op;
	float v[ARRAY_SIZE];
	//std::vector<float> v;
	float val;
	long bufSize = ARRAY_SIZE * sizeof(float);
	std::string strOp;
	char mmName[256] = "unityMemMap";

	while (true) {
		PrintOptions();
		std::cin >> strOp;
		op = std::atoi(strOp.c_str());

		switch (op)
		{
		case 1:
			std::cout << "entre nome do mapa de memória:";
			std::cin >> mmName;
			std::cout << "entre com o tamanho em quantidade de floats:";
			std::cin >> bufSize;
			std::cout << "OpenMemoryShare() return:" << OpenMemoryShare(mmName, bufSize) << std::endl;
			system("pause");
			break;
		case 2:
			std::cout << "entre nome do mapa de memória:";
			std::cin >> mmName;
			for (int i = 0; i < ARRAY_SIZE; i++) {
				std::cout << "entre valor para escrever:";
				std::cin >> val;
				//v.push_back(val);
				v[i] = val;
			}
			WriteMemoryShare(mmName, v);
			system("pause");
			break;
		case 3:
			std::cout << "entre nome do mapa de memória:";
			std::cin >> mmName;
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				v[i] = 0;
			}
			ReadMemoryShare(mmName, v);
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				std::cout << "valor lido:" << v[i] << std::endl;
			}
			system("pause");
			break;
		case 4:
			CloseAllMemoryShare();
			return 0;
			break;
		default:
			std::cout << "Opção inválida!";
			system("pause");
			break;
		}
	}


}

void PrintOptions()
{
	system("CLS");
	std::cout << "Opções:" << std::endl << std::endl;
	std::cout << "1- Abrir novo mapa de memória compartilhada." << std::endl;
	std::cout << "2- Escrever dado na memória compartilhada." << std::endl;
	std::cout << "3- Ler dado da memória compartilhada." << std::endl;
	std::cout << "4- Fechar e sair." << std::endl << std::endl;
	std::cout << "Sua escolha:";
}