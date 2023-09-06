//
//  Cash.cpp
//  GestioneElettrodomestici
//
//  Created by Filippo Bianco on 18/01/2020.
//  Copyright © 2020 Filippo Bianco. All rights reserved.
//	mat:1187400

#include "Cash.h"
#include "Appliance.h"
#include "Component.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Cash::Cash() {
    //Legge la cassa dal file.
    ifstream cash;
    try {

        cash.open("orders.dat");
        if(cash.is_open()) {


            std::string tempCash = "";
            getline(cash, tempCash);
            cash.close();
            available_cash = std::stod(tempCash);

        }else{
            std::cerr << "Impossibile leggere la cassa disponibile dal file #2. " << endl;
        }
    } catch (...) {
        cash.close();
        std::cerr << "Impossibile leggere la cassa disponibile dal file." << endl;
    }
}

bool Cash::can_afford(Order o) const {
    //Determina se l'azienda si può permettere di mandare in produzione questo elettrodomestico.
    //Il costo di produzione è determinato dalla somma dei costi delle componenti.
    //Quindi per prima cosa calcolo la somma dei costi delle componenti
    int quantity = o.get_quantity(); //La quantità di elettrodomestici da produrre.
    double total_cost = 0.0;

    list<Component>::const_iterator it = o.get_appliance().getIterator();

    for (int i = 0; i < o.get_appliance().numComponets(); i++) {

        Component comp = (*it);
        int components_needed = comp.getQty();

           if (components_needed <= 10) {
               total_cost += (components_needed * comp.getPrice1() * quantity);
           } else if (components_needed <= 50) {
               total_cost += (components_needed * comp.getPrice2() * quantity);
           } else {
               total_cost += (components_needed * comp.getPrice3() * quantity);
           }
        it++;

    }
    return (total_cost <= available_cash);
}

void Cash::pay_order(Order o) {

    int quantity = o.get_quantity(); //La quantità di elettrodomestici da produrre.
    double total_cost = 0.0;

    list<Component>::const_iterator it = o.get_appliance().getIterator();

    for (int i = 0; i < o.get_appliance().numComponets(); i++) {

      int components_needed = (*it).getQty();

       if (components_needed <= 10) {
           total_cost += (components_needed * (*it).getPrice1() * quantity);
       } else if (components_needed <= 50) {
           total_cost += (components_needed * (*it).getPrice2() * quantity);
       } else {
           total_cost += (components_needed * (*it).getPrice3() * quantity);
       }
       it++;

    }

    available_cash = available_cash - total_cost;

}
