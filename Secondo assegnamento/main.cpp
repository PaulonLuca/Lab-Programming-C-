//
//  main.cpp
//  GestioneElettrodomestici
//
//  Created by Filippo Bianco on 12/01/2020.
//  Copyright © 2020 Filippo Bianco. All rights reserved.
//	mat:1187400

#include <iostream>
#include "Orders.h"
#include "Appliance.h"
#include "Cash.h"

using namespace std;

void pt(void);
void print_order_infos(Order o);


//Funzione helper che stampa semplicemente una riga di trattini. Utile solo a scopi di design
void pt(void) {
	for (int i = 0; i < 30; i++) {
		cout << "-";
	}
	cout << endl;
}

void print_order_infos(Order o) {
	cout << "Ordine numero:" << o.get_id() << endl << "Elettodomestico: " << o.get_name() << endl << "Quantita' da produrre: " << o.get_quantity() << endl << "Costo (Rivendita): " << o.get_appliance().getPrice() << endl << "Numero componenti: " << o.components_number() << endl << endl;
}

int main(void) {
	pt();
	cout << "Benvenuto in Gestione Elettrodomestici!" << endl;
	pt();
	// Step1: raccoglie gli ordini
	Orders orders;
	Cash cash; //inizializza il gestore della cassa
	orders.init("orders.dat");

	int total_orders = orders.get_number_orders();

	int month = 0; // conta i mesi che passano
	bool already_cash = false;
	while (total_orders!=0) {
		//Verifichiamo se tutti gli ordini sono stati prodotti ed, eventualmente, incassiamone i soldi.
		if(!already_cash){
			list<Order>::const_iterator iter = orders.get_iterator();
			for (iter; iter != orders.get_end_list(); iter++) {
				if ((*iter).is_complete() && !(*iter).is_sold()){
					cash.add_cash((*iter).sale_price());
					cout << endl << "ordine id: " << (*iter).get_id()<< " completato!!"<<endl;
					cout << "Abbiamo incassato: " << (*iter).sale_price() << endl;
					cout << "la cassa ammonta a: " << cash.get_cash() << endl;
					total_orders--;
				}
			}
			//Verifichiamo se ci sono ordini che devono partire in questo mese.
			if (orders.has_order(month) > 0) {
				// facciamo partire il nuovo ordine
				list<Order>::iterator current_order = orders.get_iterator();
				for (current_order; current_order != orders.get_end_list(); current_order++) {
					//Posso far partire l'ordine?
					if ((*current_order).right_time_stamp(month) ) {
						if (cash.can_afford(*current_order)) {
							cout << "\nInizio a processare l'ordine:\n";
							print_order_infos(*current_order);
							//Toglie i soldi dalla cassa
							cash.pay_order(*current_order);
							// comincia l'ordine.
							(*current_order).start_order(); //Avvia l'ordine!
						}
						else {
							//Insufficienza di cassa: impossibile produrre l'ordine.
							cout << "L'ordine id: " << (*current_order).get_id() << ": non puo' essere pagato." << endl;
							total_orders--;
						}
					}

				}
			}
		}
		
		already_cash = true;
		//passa mese o stampa stato?
		cout << endl << "Come si desidera procedere? Digitare:\n\t-'c' per gli ordini completi\n\t-'d' per gli ordini da effettuare\n\t- Un qualsiasi carattere per passare al mese successivo\n\tComando: ";
		string command;
		cin >> command;

		std::list<Order>::const_iterator ord = orders.get_iterator();

		if (command == "d") {
			//ordini da effettuare
			cout << endl << "ORDINI DA EFFETTUARE: " << endl << "----------------------" << endl;

			for (ord; ord != orders.get_end_list(); ord++) {

				Order current_order = (*ord);
				if (!current_order.is_complete()) {
					print_order_infos(current_order);
				}
			}

		}
		else if (command == "c") {
			cout << endl << "ORDINI COMPLETATI: " << endl << "--------------------" << endl;
			ord = orders.get_iterator();

			for (ord; ord != orders.get_end_list(); ord++) {
				Order current_order = (*ord);
				if (current_order.is_complete()) {
					print_order_infos(current_order);
				}
			}
		} else{
			orders.set_sold(); //Avvisa la classe Orders che quell'ordine è stato completato.
			month++; //Passa al mese successivo.
			orders.next_month(month);
			already_cash = false;
		}

	}


	// Fine di tutti gli ordini.
	cout << "Finito di processare tutti gli ordini." << endl;
	cout << "Il saldo finale e': " << cash.get_cash() << endl;


}
