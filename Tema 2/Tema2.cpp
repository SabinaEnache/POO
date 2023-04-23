/*Tema 12. Se dau clasele :
-Card(string nrCard, string NumeDetinator, string data_expirare, int CVV, double credit)[cvv = cele 3 cifre de pe spatele cardului)
- Card_standard(int limitaExtragere, double comisionDepasireLimita) : Card
- Card premium(double cashback) : Card_Standard

Cerinte:
Sa permiteti printr - o metoda sa extrageti bani de pe un card.
Sa se verifice ca aceasta suma sa nu fie mai mare decat creditul.
Daca depaseste limita cardului standard atunci se aplica comisionul pentru diferenta de bani.
Daca se extrage de pe un card premium sa primeasca inapoi cashback / 100 * suma retrasa.

Cerint in plus:
- sa se scada comisionul persoanelor care au card premium cu 1 (dynamic cast)
-la crearea unui card nou, sa se adauge un bonus de 100 lei (pointer la clasa de baza)
-sa se afiseze cate carduri au fost crearte (functii si atribute statice)
*/

#include "tema.h"
#include <vector>
int Card::nr_carduri = 0;
int main()
{
	std::vector<std::shared_ptr<Card>> c;

	int inscriere = 1;
	while (inscriere)
	{
		int optiune;
		std::cout << "Card standard = 1, Card premium = 2" << std::endl;
		std::cin >> optiune;
		switch (optiune)
		{
			case 1: {c.push_back(std::make_unique<Card_standard>()); break;}
			case 2: {c.push_back(std::make_unique<Card_premium>()); break;}
		}
		try {
			c.back()->citire();
			Bonus b(c.back()); 
			b.add();
		}
		catch (Exceptii& e){
			std::cout << e.what() << std::endl;
			c.pop_back();
		}
		
		std::cin.ignore();
		std::cout << "Doriti inca un card? da = 1, nu = 0"<<std::endl;
		std::cin >> inscriere;
	}

	for (auto p = c.begin(); p != c.end(); p++)
	{
		if (auto derived = dynamic_cast<Card_premium*>(p->get()))
		{
			std::shared_ptr<Card_premium> card_premium_ptr = std::dynamic_pointer_cast<Card_premium>(*p);
			try
			{
				card_premium_ptr->scade();
				std::cout << "Pentru ca ati ales card premium, comisionul dvs. a scazut!" << std::endl<<std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "Eroare: " << e.what() << std::endl;
			}
		}
	}

	std::cin.ignore();
	int extragere = 1;
	while (extragere)
	{
		int optiune2;
		std::cout << "Doriti sa extrageti bani? nu = 1, da = 2" << std::endl;
		std::cin >> optiune2;
		switch (optiune2)
		{
			case 1: {break;}
			case 2: 
			{ 
				double suma;
				std::cout << "Ce suma doriti sa extrageti?" << std::endl;
				std::cin >> suma;
				if (c.size() != 1)
				{
					int optiune3;
					std::cout << "Din care dintre cele " << c.size() << " conturi?" << std::endl;
					std::cin >> optiune3;
					c[optiune3 - 1]->extrage(suma);
				}
				else
					c[0]->extrage(suma);

			}
		}
		if (optiune2 == 1) break;
		std::cin.ignore();
		std::cout << "Doriti sa faceti inca o extragere? da = 1, nu = 0" << std::endl;
		std::cin >> extragere;
	}

	
	for (auto p = 0; p != c.size(); p++)
	{
		c[p]->afisare();
	}
	return 0;
}
