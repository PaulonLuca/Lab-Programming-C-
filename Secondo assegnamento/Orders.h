//Made by Nicola Boscolo Cegion Mat:1195705
#ifndef ORDERS_H
#define ORDERS_H

#include "Component.h"
#include "Appliance.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>


class Order;
class Orders;

class Orders{

  int orders_count;
  std::list<Order> list_order;//contains all the ordesrs

public: 

  Orders():orders_count{0}{}

  void init(std::string file);//initialize data by passing the name file

  void next_month(int month);//make pass a month in all the orders

  Order& find_order(int id);//find order by id
  Order find_order(int id)const;//give a copy of the order
  bool has_order(int month)const;//say if there is a order that have to start this week
  bool list_is_complete()const;//say if they are complete orders
  int get_number_orders()const{return list_order.size();}


  std::list<Order>::iterator get_iterator(){return list_order.begin();}//funcions for accessing the list
  std::list<Order>::iterator get_end_list(){return list_order.end();}
  

  void set_sold();//set the boolean sold it the order is complete 
  //error class
  class order_not_found{};
  class file_probelm{};
};

class Order{
  struct lot{//for every order component
    
      Component compo;//type of componet
      int counter;//time of shipping
      bool ordered;
      lot(Component c, int in):compo{c},counter{in},ordered{false}{}//constructor
  };
  
  std::list<Order::lot> components;
  Appliance type;
  bool complete,sold,started;
  int quantity, time_stamp, id, max_time;
  /*id is an id of the order
  max_time is a variable used for the controll of the time
  */
  //this two function is the reason why Orders is a friend of Order, i want that only Orders can access this functions
  void update_time(int month);//update the time of a single order
  void setSold() { sold = true; }
  Order(int t,int id_applaiance, int q,int id_order);

  friend class Orders;

public:

  Order()=delete;//no standard constructor allowed 

  //get functions 
  int get_quantity()const{return quantity;}
  int get_id()const{return id;}
  int components_number()const{return components.size();}
  string get_name()const{return type.getName();}
  Appliance& get_appliance(){return type;}//return the appliance
  Appliance get_appliance()const{return type;}//return a copy of the appliance
  double sale_price()const{return type.getPrice()*quantity;}

  bool right_time_stamp(int month)const{return month==time_stamp;}
  bool is_complete()const{return complete;}
  bool is_sold()const { return sold;}

  //start the order
  void start_order(){started=true;}
  

};

#endif