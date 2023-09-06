//Made by Nicola Boscolo Cegion Mat:1195705

#include "Orders.h"
#include "Component.h"
#include "Appliance.h"
#include <iostream> 
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

using namespace std;

//CLASS ORDERS --------------------------------------------------------
void Orders::init(string filename){
    fstream file;
    try{
        file.open(filename);
        string buffer;
        getline(file, buffer);//take the first and it don't use it because is useless for this class
        
        string temp;
        int time_stamp, model_id,quantity;

        while (getline(file, buffer)){//controll the liene and takes all the data
            istringstream iss(buffer);
            
            getline(iss, temp, ' ');
            
            time_stamp=stoi(temp);
            
            getline(iss, temp, ' ');
            
            int model_id=stoi(temp);

            getline(iss, temp, ' ');
            
            int quantity=stoi(temp);
            
            orders_count++;

            list_order.push_back(Order(time_stamp,model_id,quantity, orders_count));//crea il primo ordine 
        }
        file.close();
    }catch(...){
        file.close();
        throw file_probelm();
    }
}

void Orders::next_month(int month){//update the time 
    list<Order>::iterator it=list_order.begin();;
    for(it; it!=list_order.end();it++){//evry order is updated
        (*it).update_time(month);
    }
}

Order& Orders::find_order(int id){//give the order
    list<Order>::iterator it = list_order.begin();
    
    while(it != list_order.end()){
        if((*it).get_id()==id)
            return *it;
    }
    throw order_not_found();
}

Order Orders::find_order(int id)const{//give a copy of the order
    list<Order>::const_iterator it = list_order.begin();
    
    while(it != list_order.end()){
        if((*it).get_id()==id)
            return *it;
    }
    throw order_not_found();
}

bool Orders::has_order(int month)const{//say if there is a order that have to start this week
    list<Order>::const_iterator it =  list_order.begin();

    for(it ; it!=list_order.end(); it++){
        if((*it).right_time_stamp(month))
            return true;
    }

    return false;
}

bool Orders::list_is_complete()const {//say if they are complete orders
    list<Order>::const_iterator it;
    for (it = list_order.begin(); it != list_order.end(); it++) {
        if (!(*it).is_sold())
            return false;
    }
    return true;
}

void Orders::set_sold(){//set sold the orders that are complete
    list<Order>::iterator it;

    for(it = list_order.begin(); it != list_order.end();it++){
        if ((*it).is_complete()) {
            (*it).setSold();
            orders_count--;
        }
    }
}


//CLASS ORDER -----------------------------------------------------------
Order::Order(int t,int id_applaiance, int q, int id_order)//constructor
    :time_stamp{t}, type{Appliance(id_applaiance)}, quantity{q}, id{id_order}, complete{false},max_time{0},sold{false},started{false}{
    list<Component>::const_iterator list_compo = type.getIterator();

    for(int i=0; i<type.numComponets(); i++, list_compo++){
        Component compo=*list_compo;
        
        components.push_back(lot(compo,compo.getMonthsNeeded()));
        
    }
}


void Order::update_time(int month){//update the order
    list<lot>::iterator it = components.begin();

    //if the order is not complete but not started 
    if(!complete && started && max_time!=0){
        max_time--;

        //looks all the list of components 
        for(it; it != components.end(); it++){

            if((*it).ordered){//if it is ordered it will decrese the month counter
                (*it).counter--;

            }else if((*it).counter==max_time){////else will control if it's the time to order the lot of components
                (*it).ordered=true;
                (*it).counter--;
                }
        }

        it=components.begin();

        if ((*it).counter == 0) {//if one componet is 0 that means that the order is arrived
            cout << "\nSono arrivati i componenti del'ordine id: " << id << " nome: "<< type.getName() << endl;

            for (it; it != components.end(); it++) {//print componets informations 
                cout << "\tid: " << (*it).compo.getId() << " nome: " << (*it).compo.getName() << " quantita': " << (*it).compo.getQty() << endl;
            }

        }else if((*it).counter == -1){//if one componet is -1 that means that the order is finished
            complete=true;
        }


    }else if(started && month>=time_stamp){//if the order is started and it's the righ month 
        max_time=(*it).compo.getMonthsNeeded();
        it++;

        for(it; it != components.end(); it++){//finds component with the longest shipping time 
            if(max_time<(*it).compo.getMonthsNeeded())
                max_time=(*it).compo.getMonthsNeeded();
        }
        it=components.begin();

        for(it; it != components.end(); it++){//controlls whats components have to be ordered
            if((*it).counter==max_time){//if it's time to order it will be ordered
                (*it).ordered=true;
                (*it).counter--;
            }
        }
    }
}