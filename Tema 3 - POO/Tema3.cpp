#include "Tema3header.h";

////Tema 8 – Pizzeria X testeaza un nou soft, dezvoltat in maniera OOP, pentru gestionarea 
////activitatii sale.
////Codul propriu - zis contine o clasa abstracta care contine doar metoda virtuala pura de calcul 
//// al pretului unui produs, iar din aceasta clasa deriva clasa Pizza.
//// In realizarea oricarui produs intra un anumit numar de ingrediente pentru care se cunosc 
//// denumirile,cantitatile si pretul unitar.Prețul unui produs finit este data de prețul 
//// ingredientelor plus manopera(o suma constanta fixata de producator).
////Daca pizza este comandata OnLine, la preț se mai adauga si 5 % din pret la fiecare 10 km 
//// parcursi de angajatul care livreaza la domiciliu.
////Structura de date : unordered_map sau unordered_set <id_pizza, list sau vector <ingredient>>
////
////Cerința suplimentara :
////-Să se adauge toate campurile relevante pentru modelarea acestei probleme.
////- Să se construiasca clasa template Meniu care sa gestioneze tipurie de pizza comercializate.
//// Clasa trebuie sa contina indexul unui produs (incrementat automat la vanzarea unui produs  
//// prin supraincarcarea operatorului += ) și o structură de date, alocata dinamic.
////- Sa se construiasca o specializare pentru tipul Comanda_Online care sa trateze tipurile de 
//// pizza vegetariana intr-un document contabil separat din care sa rezulte valoarea totala 
////incasata din vanzarea acestora.

int main() {
    Meniu<Pizza> meniu;
    Meniu<Comanda_Online> meniuOnline;

    Pizza* pizzaSimpla = new PizzaSimpla();
    meniu += pizzaSimpla;

    std::vector<Ingredient> ingrediente1 = { { "mozzarella", 2, 5 }, { "sos de rosii", 1, 3 }, { "sunca", 7, 4 }, {"porumb",1,6}};
    Pizza pizza2(2,"Clasica", ingrediente1);
    meniu += &pizza2;
    meniuOnline += &pizza2;

    std::vector<Ingredient> ingrediente2 = { { "mozzarella", 2, 5 }, { "sos de rosii", 1, 3 }, { "legume", 10, 2 } };
    Pizza pizza3(3, "Vegetariana", ingrediente2);
    meniu += &pizza3;
    meniuOnline += &pizza3;

    std::vector<Ingredient> ingrediente3 = { { "mozzarella", 2, 5 }, { "sos de rosii", 1, 3 }, { "peperoni", 10, 3 } };
    Pizza pizza4(4, "Peperoni", ingrediente3);
    meniu += &pizza4;
    meniuOnline += &pizza4;

    std::vector<Ingredient> ingrediente4 = { { "mozzarella", 2, 5 }, { "sos de rosii", 1, 3 }, { "pui", 7, 4 }, {"carnati", 1, 5}};
    Pizza pizza5(5, "Taraneasca", ingrediente4);
    meniu += &pizza5;
    meniuOnline += &pizza5;

    int optiune1;
    std::cout << "Vezi o pizzerie, ce faci? 1.Intrii, 2.Nu intrii" << std::endl;
    std::cin >> optiune1;
    while (optiune1) 
    {
        switch (optiune1) 
        {
        case 1: 
        {
            int optiune2;
            std::cout << "Bun venit la Pizzaria X, ce ati dori sa faceti?" << std::endl;
            std::cout << "1. Vedeti meniul" << std::endl << "2. Comandati pentru aici" << std::endl << "3. Comandati online pentru livrare" << std::endl << "4. Pizza personalizata"<<std::endl<<"5. Iesiti" << std::endl;
            std::cin >> optiune2;
            float total = 0;
            while (optiune2)
            {
                switch (optiune2)
                {
                    case 1:
                    {
                        meniu.afisareMeniu();
                        optiune2 = 0;
                        break;
                    }
                    case 2:
                    {
                        int optiune3;
                        std::string nume;
                        std::cout << "Ce doriti sa comandati?" << std::endl;
                        std::cin >> optiune3;
                        total+= meniu.alegePizza(optiune3);
                        std::cout << "Totalul dumneavoastra este " << total << std::endl;
                        break;
                    }
                    case 3:
                    {
                        int optiune4, distanta;
                        std::cout << "Ce doriti sa comandati?" << std::endl;
                        std::cin >> optiune4;
                        total += meniuOnline.comandaPizza(optiune4);
                        while (optiune4)
                        {
                            std::cout << "Altceva? Daca da, selectati din meniu, daca nu, selectati 0"<<std::endl;
                            std::cin >> optiune4;
                            total += meniuOnline.comandaPizza(optiune4);
                        }
                        std::cout << "Cat de departe locuiti (in km)?" << std::endl;
                        std::cin >> distanta;
                        total = meniuOnline.calculDistanta(total, distanta);
                        std::cout << "Totalul dumneavoastra este " << total << std::endl;
                        break;
                    }
                    case 4:
                    {
                        std::cout << "Ce ingredient doriti sa adaugati pe pizza?" << std::endl;
                        std::string ingr;
                        std::cin >> ingr;
                        Pizza* pizzaNoua = new DecoratorIngrediente(pizzaSimpla, ingr);
                        total += pizzaNoua->calculPret();
                        std::cout << "Totalul dumneavoastra este " << total << std::endl;
                        delete pizzaNoua;
                    }
                    case 5:
                    {
                        optiune2 = 0;
                        break;
                    }
                }
                std::cout << "Doriti sa mai faceti ceva? Daca da, selectati optiunea, daca nu, alegeti 0" << std::endl;
                std::cin >> optiune2;
            }
            //std::cout << "Totalul dumneavoastra este " << total << std::endl;
        }
        case 2: 
        {
            optiune1 = 0;
            break;
        }
        }
    }
   

    std::cout << "Pretul total al pizzelor vegetariene comandate online: "; meniuOnline.vegetariene();std::cout << std::endl;



    return 0;
}