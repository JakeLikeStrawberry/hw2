#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "mydatastore.h"

using namespace std;

   MyDataStore::MyDataStore(){      //constructor

   }

   MyDataStore::~MyDataStore(){     //deconstructor
    for (set<Product*>::iterator iterate = allProducts.begin(); iterate != allProducts.end(); iterate++){
      delete *iterate;      //deletes allProducts
    }
    for (map<std::string, User*>::iterator iterate = allUsers.begin(); iterate != allUsers.end(); iterate++){
        delete iterate->second;
    }       //deletes allUsers
   }

   void MyDataStore::clear(){       //clears variables
     allProducts.clear();
     allUsers.clear();
     userCart.clear();

   }

   /**
   * Adds a product to the data store
   */
     void MyDataStore::addProduct(Product* p){
       
        set<string> resultFinal;

        resultFinal = p->keywords();    //adds keywords from the product to this set
      
        set<string>::iterator iterate;
        for (iterate = resultFinal.begin(); iterate != resultFinal.end(); iterate++){

           if (totalStore.find(*iterate) == totalStore.end()) {   

              if (totalStore.find(*iterate) != totalStore.end()){
                break;
              }

               set<Product*> newProd;
               totalStore.insert(make_pair(*iterate, newProd));        //this puts the set with the keywords
               totalStore[*iterate].insert(p);

           }

           else{
              totalStore[*iterate].insert(p);
           }
        }
        allProducts.insert(p);      //inserts product into product map
     }

      //Adds a product to the cart
     void MyDataStore::addtoCart(string username, Product* p){
          // cout << "made it here" << endl;
        if (allUsers.find(username) == allUsers.end()) {
          cout << "Invalid request." << endl;
          return;
        }
        userCart[username].push_back(p);  

     }




      //displays whats in their cart
     void MyDataStore::viewCart(string username){
        //access userCart here?
        // set<Product* p>::iterator it2;

        std::map<std::string, vector<Product*>>::iterator it;
        it = userCart.find(username);
        int count = 1;
        if (it != userCart.end()){
          for (unsigned int i = 0; i < it->second.size(); i++){
            cout << "Item " << count << endl;
           string res = it->second[i]->displayString();            //access the vectors items, calls displayString on product
           cout << res << endl;
           count++;
          }

        }
        else{
          cout << "Invalid username" << endl;       
        }
     }


     /**
     * Adds a user to the data store
     */

     void MyDataStore::addUser(User* u){
        vector<Product*> p;
        // cout <<"hi im in here" << endl;
        string temp = convToLower(u->getName());
        // allUsers.insert(make_pair(u->getName(), p));
        
        allUsers.insert({temp, u});       //inserts into both users and usercart, since both use usernames
        userCart.insert({temp, p});

     }

     void MyDataStore::buyCart(string username){               //if item is in stock and user has enough money
                                                //then remove from stock, in stock quantity -1, product price debited from users balance 
      //std::map<std::string, vector<Product*>>::iterator it;
      //std::map<string, User*>::iterator it2;

    if(allUsers.find(username) == allUsers.end()){
      cout << "Invalid username" << endl;
      return;
    }
    // cout <<"made it here" << endl;
      for (std::vector<Product*>::iterator it = userCart[username].begin(); it < userCart[username].end();){
          if (((*it)->getQty() >= 1) && (allUsers[username])->getBalance() > (*it)->getPrice()){
            // cout << "in the loop" <<endl;
            (allUsers[username])->deductAmount((*it)->getPrice());
            (*it)->subtractQty(1);
            (userCart[username]).erase(it);
          }
          else{
            it++;
          }
      }

      // it = userCart.find(username);
      // it2 = allUsers.find(username);
      // if (it != userCart.end()){
      //   for (unsigned int i = 0; i < it->second.size(); i++){
      //     if(it->second[i]->getQty() >= 1 && (it2->second->getBalance() >= it->second[i]->getPrice())){
      //       it->second[i]->subtractQty(1);            //subtracts stock
      //       it2->second->deductAmount(it->second[i]->getPrice());       //deducts from balance
      //       it->second.erase(it->second.begin()+i);       //removes it from the users cart

      //     }
      //   }
      // }



      // else{
      //   cout << "Invalid username" << endl;
      // }

     }
     
      /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */

     std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

        //cout << "made it to beginning" << endl;
        set<Product*> resultSet = totalStore[terms[0]];    //adds to set so its not empty
        //set<Product*> resultSet;                                //will convert to vector later, ensures we dont have empty set so intersection or union works
        //cout << "this is a test" << endl; 
        for (vector<string>::iterator it = terms.begin(); it != terms.end(); it++){
          if (totalStore.find(*it) != totalStore.end()){

            if (type == 0){
             // cout << "this is a test" << endl;
              resultSet = setIntersection(resultSet, totalStore[*it]);   //made sure both are sets
              //cout <<"this is test 2" << endl;
            }

            else if (type == 1){
              resultSet = setUnion (resultSet, totalStore[*it]);   //same here
            }
          }
        }
        vector<Product*> result(resultSet.begin(), resultSet.end());    //change the set to the return type, which is vector
        return result;

        }
      /**
     * Reproduce the database file from the current Products and User values
     */

     void MyDataStore::dump(std::ostream& ofile) {
        ofile << "<products>" << endl;

        set<Product*>::iterator it;

        for (it = allProducts.begin(); it != allProducts.end(); it++){
          (*it)->dump(ofile);
        }
        ofile << "</products>" << endl;       

        ofile << "<users>" << endl;
        map<string, User*>::iterator iterate;

        for(iterate = allUsers.begin(); iterate != allUsers.end(); iterate++){
            (*iterate).second->dump(ofile);
        }

        ofile << "</users>" << endl;
     }
  
