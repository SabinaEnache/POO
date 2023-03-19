#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
//CERINTA LUATA DIN POO - TEMA 1 - V2 EXERCITIUL NR 4
//Se considera urmatoarele clase:
//Data ce contine atributele: zi(int), luna(sir de caractere de lungime fixa 20), an(int).
//Actor ce contine atributele: nume(sir de caractere de lungime variabila), data_nasterii(Data).
//Film ce contine atributele: titlu(sir de caractere de lungime fixa 50), nrActori(int), Act(vector de obiecte de tip Actor).

//Definiti clasele si completati-le cu metode si supraincarcari de operatori pentru a permite in functia main() urmatoarele operatii:
//Data d1(15,"iulie",1975), d2=d1;
//Actor a1("Ionescu",d1),a2("Popescu",2,"ianuarie",1980);
//Film f1("Matrix"), f2, f3;
//!!!!f1+=p1; // adauga actorul a1 in lista filmului f1
//f1+=p2;!!! // adauga actorul a2 in lista filmului f1!!!!
//cout<<f1;
//!!!!cin>>f2;
//f3 = f2;
//cout<<f3;!!!!


class Data
{
private:
	int zi=0;
	string luna="";
	int an=0;
public:
	Data()
	{
		//cout<<"sunt in constructor de initializare"<<endl;
	};
	
	Data(const int& ziP)
	{
		zi = ziP;
	};
	
	Data(const int& ziP, const string& lunaP, const int& anP)
	{
		//cout<<"sunt in constructor cu mai multi parametrii pentru Data"<<endl;
		zi = ziP;
		for(int i=0;i<std::min<int>(20,lunaP.length());i++)
			luna = luna + lunaP[i];
		an = anP;
	};
	
	Data(const Data& other)
		:zi(other.zi), luna(other.luna), an(other.an)
	{
		//cout<<"sunt in constructor de copiere pentru Data"<<endl;
	}
	Data& operator=(const Data& other)
	{
		//cout<<"sunt in operator= pentru Data"<<endl;
		zi = other.zi;
		for(int i=0;i<min<int>(20,other.luna.length());i++)
			luna = luna + other.luna[i];
		an = other.an;
		return *this;
	};
	friend ostream& operator<<(ostream& os, const Data& data);
	friend istream& operator>>(istream& is, Data& data);
	~Data()
	{
		//cout<<"sunt in destructor data"<<endl;
	};
	void setZi(const int& ziP){
		zi = ziP;
	};
	void setLuna(const string& lunaP){
		luna = lunaP;
	};
	void setAn(const int& anP){
		an = anP;
	};
	int getZi(){
		return zi;
	}
	string getLuna(){
		return luna;
	};
	int getAn(){
		return an;
	};
};
ostream& operator<<(ostream& os, const Data& data)
{
	//"sunt in operator<< pentru data ";
	if(data.zi != 0)
		if(data.luna != "")
			if(data.an != 0)
				os <<data.zi << " " << data.luna<<" "<< data.an<<" ";
			else os<<data.zi<<" "<<data.luna<<" ";
		else
			if(data.an == 0)
				os<<data.zi<<" ";
	else
		if(data.luna != "")
			if(data.an != 0)
				os << data.luna << " " << data.an<<" ";
			else os << data.luna<<" ";
		else os << data.an<<" ";
	return os;
};
istream& operator>>(istream& is, Data& data)
{
	cout<<"Data nasterii este: ";
	is >> data.zi >> data.luna >> data.an;
	return is;
};

class Actor 
{
private:
	string nume;
	Data data_nasterii;
public:
	Actor()
	{
		//cout<<"sunt in consstuctor de initalizare pentru Actor";	
	};
	Actor(const string& numeP, const Data& dataN)
	{	
		//cout<<"sunt in constructor cu 2 parametrii pentru Actor"<<endl;
		nume = numeP;
		data_nasterii = dataN;
	};
	Actor(const string& numeP,const int& ziP, const string& lunaP, const int& anP)
	{
		//cout<<"sunt in constructor cu 4 parametrii pentru Actor"<<endl;
		nume = numeP;
		data_nasterii.setZi(ziP);
		data_nasterii.setLuna(lunaP);
		data_nasterii.setAn(anP);
	};
	Actor(const Actor& other)
		:nume(other.nume), data_nasterii(other.data_nasterii)
	{
		//cout<<"sunt in constructor de copiere pentru Actor"<<endl;
	};
	~Actor()
	{
		//cout<<"sunt in destructor Actor"<<endl;
	};
	void setNume(const string& numeP)
	{
		nume = numeP;
	};
	void setData(const int& ziP, const string& lunaP, const int& anP)
	{
		data_nasterii.setZi(ziP);
		data_nasterii.setLuna(lunaP);
		data_nasterii.setAn(anP);
	};
	string getNume()
	{
		return nume;
	};
	Data& getData()
	{
		return data_nasterii;
	};
	Actor& operator=(const Actor& other)
	{
		//cout<<"sunt in operator= pentru Actor"<<endl;
		nume = other.nume;
		data_nasterii = other.data_nasterii;
		return *this;
	};
	friend ostream& operator<<(ostream& os, const Actor& a);
	friend istream& operator>>(istream& is, Actor& a);
};
ostream& operator<<(ostream& os, const Actor& a)
{
	// cout<<"sunt in operator<< pentru Actor " ;
	os <<"Numele actorului este " << a.nume << " si este nascut pe " <<a.data_nasterii<<" ";
	return os;
};
istream& operator>>(istream& is, Actor& a)
{
	cout<<"Numele si data nasterii actorului sunt:";
	is >> a.nume >> a.data_nasterii;
	return is;
};

class Film{
private:
	string titlu;
	int nrActori=0;
	vector<Actor> Act;
public:
	Film()
	{
		//cout<<"sunt in constructor defaul pentru film";
	};
	Film(const string& titluP)
	{
		for(int i=0;i<std::min<int>(50,titluP.length());i++)
			titlu = titlu + titluP[i];
	};
	Film(const string& titluP, const int& nr, const Actor& a)
	{
		for(int i=0;i<min<int>(50,titluP.length());i++)
			titlu = titlu + titluP[i];
		nrActori = nr;
		Act.push_back(a);
	}; 
	friend ostream& operator<<(ostream& os, const Film& f);
	
	Film& operator=(const Film& other)
	{
		//cout<<"sunt in operator= pentru Film"<<endl;
		titlu = other.titlu;
		nrActori = other.nrActori;
		Act = vector<Actor>(other.Act);
		return *this;
	};
	void add_actor(Actor& other)
	{
		Act.push_back(other);
	};
	friend istream& operator>>(istream& is, Film& f)
	{
		Actor actor;
		is >> f.titlu >> f.nrActori>>actor;
		f.add_actor(actor);
		return is;
	};
	Film& operator+=(const Actor& other)
	{
		Act.push_back(other);
		nrActori = nrActori + 1;
	};
	void print_actor() const 
	{
    	for (int i = 0; i < Act.size(); i++) 
		{
        	cout << Act[i]<<" ";
    	}
	};
	void setNume(const string& numeF)
	{
		titlu = numeF;
	};
	void setNr(const int& nr)
	{
		nrActori = nr;
	};
	string getTitlu()
	{
		return titlu;
	};
	int getNr()
	{
		return nrActori;
	};
};

ostream& operator<<(ostream& os, const Film& f)
{
	if(f.nrActori != 0)
		{
			os << f.titlu << ", " << f.nrActori<<", ";
			f.print_actor();
			os << " ";
		}
	else os << f.titlu <<endl;
	return os;
};
int main()
{
	Data d1(15,"iulie",1975), d2=d1;
	Actor a1("Ionescu",d1), a2("Popescu",2,"ianuarie",1980);
	Film f1("Matrix"),f2,f3;
	f1 += a1;
	f1 += a2;
	cout<<f1<<endl;
	cin>>f2;
	f3 = f2;
	cout<<f3;
	
	return 0;
}
