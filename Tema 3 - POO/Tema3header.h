
#pragma once

#include <iostream>
#include<vector>
#include <unordered_map>

//Tema 8 – Pizzeria X testeaza un nou soft, dezvoltat in maniera OOP, pentru gestionarea 
//activitatii sale.
//Codul propriu - zis contine o clasa abstracta care contine doar metoda virtuala pura de calcul 
// al pretului unui produs, iar din aceasta clasa deriva clasa Pizza.
// In realizarea oricarui produs intra un anumit numar de ingrediente pentru care se cunosc 
// denumirile,cantitatile si pretul unitar.Prețul unui produs finit este data de prețul 
// ingredientelor plus manopera(o suma constanta fixata de producator).
//Daca pizza este comandata OnLine, la preț se mai adauga si 5 % din pret la fiecare 10 km 
// parcursi de angajatul care livreaza la domiciliu.
//Structura de date : unordered_map sau unordered_set <id_pizza, list sau vector <ingredient>>
//
//Cerința suplimentara :
//-Să se adauge toate campurile relevante pentru modelarea acestei probleme.
//- Să se construiasca clasa template Meniu care sa gestioneze tipurie de pizza comercializate.
// Clasa trebuie sa contina indexul unui produs (incrementat automat la vanzarea unui produs  
// prin supraincarcarea operatorului += ) și o structură de date, alocata dinamic.
//- Sa se construiasca o specializare pentru tipul Comanda_Online care sa trateze tipurile de 
// pizza vegetariana intr-un document contabil separat din care sa rezulte valoarea totala 
//incasata din vanzarea acestora.


class Pret 
{
public:
    virtual float calculPret() const = 0;
};

class Ingredient 
{
protected:
    std::string denumire;
    float cantitate;
    float pretUnitar;
public:
    Ingredient() = default;
    Ingredient(const std::string d, const float c, const float p)
        :denumire(d),cantitate(c),pretUnitar(p){}
    std::string getDenumire() const { return denumire; }
    float getCantitate() const { return cantitate; }
    float getPret() const { return pretUnitar; }
    ~Ingredient()=default;
};

class Pizza : public Pret, public Ingredient 
{
protected:
    int id_pizza;
    std::string denumire;
    std::vector<Ingredient> ingrediente;
    static const float manopera;

public:
    Pizza() = default;
    Pizza(const int id, const std::string d, const std::vector<Ingredient>& ingr) : id_pizza(id), denumire(d), ingrediente(ingr) {}

    float calculPret() const override 
    {
        float total = 0.0;
        for (const auto& ingredient : ingrediente) 
        {
            total += ingredient.getCantitate() * ingredient.getPret();
        }
        total += manopera;
        return total;
    }
    int getId() const { return id_pizza; }
    std::string getNume() const { return denumire; }
    std::vector<Ingredient> getIngrediente() const { return ingrediente; }
    ~Pizza() = default;
};

const float Pizza::manopera = 2.5;

class PizzaSimpla : public Pizza 
{
public:
    PizzaSimpla() : Pizza(1, "Simpla", { {"mozzarella", 2, 5}, {"sos de rosii", 1, 3} }) {}
};

class DecoratorPizza : public Pizza 
{
protected:
    Pizza* pizzaDecorata;

public:
    DecoratorPizza(Pizza* pizza) : pizzaDecorata(pizza) {}

    float calculPret() const override 
    {
        return pizzaDecorata->calculPret();
    }
};

class DecoratorIngrediente : public DecoratorPizza 
{
private:
    std::string ingredientAdaugat;
    //float pretIngredientAdaugat;

public:
    DecoratorIngrediente(Pizza* pizza, const std::string& ingredient)
        : DecoratorPizza(pizza), ingredientAdaugat(ingredient) {}

    float calculPret() const override 
    {
        float pret = DecoratorPizza::calculPret();  // Apelul metodei din decoratorul anterior
        pret += 5;  // Adaugarea pretului ingredientului adaugat
        return pret;
    }
};

template <typename T>
class Iterator 
{
public:
    virtual bool hasNext() const = 0;
    virtual T* next() = 0;
    virtual ~Iterator() {}
};

template <typename T>
class MeniuIterator : public Iterator<T> {
private:
    std::unordered_map<int, T*>& produse;
    typename std::unordered_map<int, T*>::iterator current;

public:
    MeniuIterator(std::unordered_map<int, T*>& produse) : produse(produse), current(produse.begin()) {}

    bool hasNext() const override {
        return current != produse.end();
    }

    T* next() override {
        T* nextItem = current->second;
        ++current;
        return nextItem;
    }
};

template <typename T>
class Meniu : public Pizza {
private:
    int indexProdus;
    std::unordered_map<int, T*> produse;
public:
    Meniu() : indexProdus(1) {}

    void operator+=(T* produs) {
        produse[indexProdus] = produs;
        indexProdus++;
    }

    void afisareMeniu() 
    {
        MeniuIterator<T> iterator(produse);
        while (iterator.hasNext()) {
            const Pizza* pizza = iterator.next();
            std::cout << "Pizza " << pizza->getNume() << ": " << std::endl;
            for (const auto& ingredient : pizza->getIngrediente()) {
                std::cout << "  - " << ingredient.getDenumire() << std::endl;
            }
            std::cout << "Pret: " << pizza->calculPret() << std::endl;
            std::cout << std::endl;
        }
    }

    Iterator<T>* createIterator() {
        return new MeniuIterator<T>(produse);
    }

    float alegePizza(const int optiune) {
        for (auto& pair : produse) {
            const Pizza* pizza = pair.second;
            if (pizza->getId() == optiune)
                return pizza->calculPret();
        }
    }
    ~Meniu() = default;
};

class Comanda_Online {};

template <>
class Meniu<Comanda_Online> :public Pizza{
private:
    int indexProdus;
    std::unordered_map<int, Pizza*> produse;
    float totalVegetariene;
public:
    Meniu() : indexProdus(1), totalVegetariene(0.0) {}

    void operator+=(Pizza* pizza) {
        produse[indexProdus] = pizza;
        indexProdus++;
    }

    float comandaPizza(const int optiune) 
    {
        for (auto& pair : produse) 
        {
            const Pizza* pizza = pair.second;
            if (pizza->getId() == optiune)
            {
                bool isVegetariana = false;
                for (const auto& ingredient : pizza->getIngrediente()) {
                    if (ingredient.getDenumire() == "legume") {
                        isVegetariana = true;
                        break;
                    }
                }
                if (isVegetariana) {
                    totalVegetariene += pizza->calculPret();
                }
                return pizza->calculPret();
            }
        }

    }
    float calculDistanta(const float t, const int d) 
    {
        return t+t*0.05*(d/10);
    }
    void vegetariene() {
        std::cout << totalVegetariene;
    }
    ~Meniu<Comanda_Online>() = default;
};



