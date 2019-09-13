// useUnityComCpp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "pch.h"
#include <iostream>
#include "../UnityComCpp/UnityCom.h"

void PrintOptions();

int main()
{
	float a = 3.2;
	float b = 4.2;
	float c = Add(a, b);
	std::cout << c << std::endl;
	std::cout << "OpenMemoryShare() return:" << OpenMemoryShare() << std::endl;
	system("pause");

	int op;
	float v;

	while (true) {
		PrintOptions();
		std::cin >> op;
		switch (op)
		{
		case 1:
			std::cout << "entre valor para escrever:";
			std::cin >> v;
			WriteMemoryShare(v);
			break;
		case 2:
			v = ReadMemoryShare();
			std::cout << "valor lido:" << v << std::endl;
			system("pause");
			break;
		case 3:
			EndMemoryShare();
			return 0;
			break;
		default:
			break;
		}
	}


}

void PrintOptions()
{
	system("CLS");
	std::cout << "Opções:" << std::endl << std::endl;
	std::cout << "1- Escrever dado na memória compartilhada" << std::endl;
	std::cout << "2- Ler dado da memória compartilhada" << std::endl;
	std::cout << "3- Sair" << std::endl << std::endl;
	std::cout << "Sua escolha:";
}