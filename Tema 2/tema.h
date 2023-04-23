#pragma once
#include <iostream>
/*Tema 12. Se dau clasele :
-Card(string nrCard, string NumeDetinator, string data_expirare, int CVV, double credit)[cvv = cele 3 cifre de pe spatele cardului)
- Card_standard(int limitaExtragere, double comisionDepasireLimita) : Card
- Card premium(double cashback) : Card_Standard

Cerinte:
Sa permiteti printr - o metoda sa extrageti bani de pe un card.
Sa se verifice ca aceasta suma sa nu fie mai mare decat creditul.
Daca depaseste limita cardului standard atunci se aplica comisionul pentru diferenta de bani.
Daca se extrage de pe un card premium sa primeasca inapoi cashback / 100 * suma retrasa.
*/
class Card {
protected:
	std::string nrCard;
	std::string NumeDetinator;
	std::string data_expirare;
	int cvv;
	double credit;
	static int nr_carduri;
public:
	Card()
	{
		//std::cout << "sunt in constructor default" << std::endl;
		nr_carduri++;
	}

	Card(const std::string& nrCard2, const std::string& NumeDetinator2, const std::string& data_expirare2, const int& cvv2, const double& credit2)
	{
		nrCard = nrCard2;
		NumeDetinator = NumeDetinator2;
		data_expirare = data_expirare2;
		cvv = cvv2;
		credit = credit2;
		//std::cout << "sunt in constructor cu parametri" << std::endl;
		nr_carduri++;
	}

	Card(const Card& other)
		: nrCard(other.nrCard), NumeDetinator(other.NumeDetinator), data_expirare(other.data_expirare), cvv(other.cvv), credit(other.credit)
	{
		//std::cout << "sunt in constructor de copiere pentru Card" << std::endl;
	};
	~Card() 
	{
		//std::cout << "sunt in destructor pentru Card" << std::endl;
	};

	void SetNr(const std::string& other)
	{
		nrCard = other;
	};
	void SetNume(const std::string& other)
	{
		NumeDetinator = other;
	};
	void SetData(const std::string& other)
	{
		data_expirare = other;
	};
	void SetCVV(const int& other)
	{
		cvv = other;
	};
	void SetCredit(const double& other)
	{
		credit = other;
	}

	std::string GetNr() const 
	{
		return nrCard;
	};
	std::string GetNume() const
	{
		return NumeDetinator;
	};
	std::string GetData() const 
	{
		return data_expirare;
	};
	int GetCVV() const 
	{
		return cvv;
	};
	double GetCredit() const
	{
		return credit;
	};

	virtual void citire() = 0;
	virtual void afisare() = 0;
	virtual void extrage(const double& suma) = 0;
	virtual void add()
	{
		credit += 100;
		std::cout << "Ati primit un bonus de 100 lei la crearea noului card!" << std::endl;
	};

	static void nrCarduri() {
		std::cout << nr_carduri << std::endl;
	}

	Card& operator=(const Card& other)
	{
		//std::cout<<"sunt in operator= pentru card"<<std::endl;
		if (this != &other)
		{
			nrCard = other.nrCard;
			NumeDetinator = other.NumeDetinator;
			data_expirare = other.data_expirare;
			cvv = other.cvv;
			credit = other.credit;
		}
		return *this;
	};
};
class Card_standard : public Card {
protected:
	int limitaExtragere;
	double comisionDepLim;
public:
	Card_standard() 
	{ 
		//std::cout << "sunt in constructor default pentru card standard" << std::endl; 
	};
	Card_standard(const Card_standard& other)
		: Card(other), limitaExtragere(other.limitaExtragere), comisionDepLim(other.comisionDepLim)
	{
		//std::cout << "sunt in constructor de copiere pentru card standard" << std::endl;
	};
	~Card_standard() {};
	void SetLimita(const int& other)
	{
		limitaExtragere = other;
	};
	void SetComision(const double& other) 
	{
		comisionDepLim = other;
	};
	int GetLimita() const
	{
		return limitaExtragere;
	};
	double GetComision() const
	{
		return comisionDepLim;
	};

	void citire();
	void afisare();
	void extrage(const double& suma);
	virtual void scade();

	Card_standard& operator=(const Card_standard& other)
	{
		//std:cout<<"sunt in operator= pentru card standard"<<std::endl;
		if (this != &other)
		{
			Card::operator=(other);
			limitaExtragere = other.limitaExtragere;
			comisionDepLim = other.comisionDepLim;
		}
		return *this;
	};
};
class Card_premium : public Card_standard {
protected:
	double cashback;
public:
	Card_premium()
	{
		//std::cout << "sunt in constructor default pentru card premium" << std::endl;
	}
	Card_premium(const Card_premium& other)
		: Card_standard(other), cashback(other.cashback)
	{
		//std::cout << "sunt in constructor de copiere pentru card premium" << std::endl;
	};
	~Card_premium() {};
	void SetCahsback(const double& other)
	{
		cashback = other;
	};
	double GetCashback() const
	{
		return cashback;
	};

	void citire();
	void afisare();
	void extrage(const double& suma);
	void scade();

	Card_premium& operator=(const Card_premium& other)
	{
		//std::cout << "sunt in operator= pentru card pemium" << std::endl;
		if (this != &other)
		{
			Card_standard::operator=(other);
			cashback = other.cashback;
		}
		return *this;
	};
};
class Bonus {
private:
	std::shared_ptr<Card> cardPtr;
public:
	Bonus(std::shared_ptr<Card> ptr) : cardPtr(ptr) {}
	void add(){
		cardPtr->add();
	}
};

class Exceptii : public std::exception {
public:
	virtual const char* what() const noexcept override
	{
		return "Exista o eroare!";
	}
};
class NrInvalid : public Exceptii {
public:
	virtual const char* what() const noexcept override
	{
		return "Numarul cardului este invalid!";
	}
};
class DataInvailda : public Exceptii {
public:
	virtual const char* what() const noexcept 
	{
		return "Data introdusa este invalida!";
	}
};
class CVVInvalid: public Exceptii{
public:
	virtual const char* what() const noexcept override
	{
		return "CVV-ul este invalid!";
	}
};

void Card::citire()
{
	std::cout << "Numar card: ";
	std::cin >> nrCard;
	if (nrCard.size() != 16)
	{
		throw NrInvalid();
	}

	std::cout << "Nume detinator: ";
	std::cin >> NumeDetinator;

	std::cout << "Data expirarii: ";
	std::cin >> data_expirare;
	if (data_expirare.size() != 5 or data_expirare[2] != '/')
	{
		throw DataInvailda();
	}

	std::cout << "CVV: ";
	std::cin >> cvv;
	if (cvv <= 100 or cvv >= 1000)
	{
		throw CVVInvalid();
	}
	std::cout << "Credit: ";
	std::cin >> credit;
};
void Card_standard::citire()
{
	Card::citire();
	std::cout << "Limita extragere: ";
	std::cin >> limitaExtragere;
	std::cout << "Comision depasire limita: ";
	std::cin >> comisionDepLim;
};
void Card_premium::citire()
{
	Card_standard::citire();
	std::cout << "Cashback: ";
	std::cin >> cashback;
};

void Card::afisare()
{
	Card::nrCarduri();
	std::cout << "Numar card " << nrCard << ", nume detinator " << NumeDetinator << ", data expirarii " << data_expirare << ", CVV " << cvv << ", credit " << credit << " lei";
};
void Card_standard::afisare()
{
	Card::afisare();
	std::cout << ", limita extragere " << limitaExtragere << ", comision depasire limita " << comisionDepLim << "%";
};
void Card_premium::afisare()
{
	Card_standard::afisare();
	std::cout << ", cashback " << cashback << "%" << std::endl << std::endl;
};

void Card::extrage(const double& nr)
{
	if (nr <= credit)
		credit = credit - nr;
	else std::cout << "Nu se poate efectua extragerea" << std::endl;
};
void Card_standard::extrage(const double& nr)
{
	if (nr <= credit)
		if (nr <= limitaExtragere) Card::extrage(nr);
		else credit = credit - nr - ((nr - limitaExtragere) * (comisionDepLim / 100));
	else std::cout << "Nu se poate efectua extragerea" << std::endl;
};
void Card_premium::extrage(const double& nr)
{
	if (nr <= credit)
		if (nr <= limitaExtragere) 
		{
			Card_standard::extrage(nr);
			credit = credit + (cashback / 100) * nr;
		}
		else credit = credit - nr - ((nr - limitaExtragere) * (comisionDepLim / 100)) + nr * (cashback / 100);
	else std::cout << "Nu se poate efectua extragerea" << std::endl;
};

void Card_standard::scade()
{
	if (comisionDepLim == 0)
	{
		throw std::invalid_argument("Comisionul nu poate fi mai mic decat 0%.");
	}
	comisionDepLim = comisionDepLim - 1;
};
void Card_premium::scade()
{
	if (comisionDepLim == 0)
	{
		throw std::invalid_argument("Comisionul nu poate fi mai mic decat 0%.");
	}
	comisionDepLim = comisionDepLim - 1;
};


