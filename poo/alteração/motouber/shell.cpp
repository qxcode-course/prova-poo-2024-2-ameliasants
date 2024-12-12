#define __MEMORY //enable print for shared_ptr
#include "fn.hpp"

class Person{
private:
   std::string name;
   int money;
public:
   Person(std::string name, int money): name(name), money(money) {}

   std::string getName(){
     return this->name;
   }

   int getMoney(){
     return this->money;
   }

    void pagar(int valor) {
     if (this->money < valor) 
     this->money = 0; 
     else 
     this->money -= valor;
    }
   void receber(int valor) { 
    this->money += valor; 
   }
   std::string str() const{
     return fn::format("{}:{}", this->name, this->money);
   }
};

class Uber{
    private:
        int money{0};
        std::shared_ptr<Person> motorista{nullptr};
        std::shared_ptr<Person> passageiro{nullptr};

    public:
        Uber(): money(0) , motorista(nullptr), passageiro(nullptr){}

     void setDriver(std::shared_ptr<Person> motorista) {
        if (this->motorista != nullptr) {
            std::cout << "fail: Driver is already set\n";
            return;
        }
        this->motorista = motorista;
    }
     void setPass(std::shared_ptr<Person> passageiro){
       if (this->motorista == nullptr) {
            std::cout << "fail: No driver, no passenger\n";
            return;
        }
        if (this->passageiro != nullptr) {
            std::cout << "fail: Passenger is already set\n";
            return;
        }
        this->passageiro = passageiro;
  }
     void drive(int distance){
         if (this->motorista == nullptr || this->passageiro == nullptr) {
            std::cout << "fail: Missing driver or passenger\n";
            return;
        }
        this->money += distance;
    }      

      void leavePass() {
        if (this->passageiro == nullptr) {
            std::cout << "fail: No passenger to leave\n";
            return;
        }
       if (passageiro->getMoney() < money) {
                std::cout << "fail: Passenger does not have enough money\n";
        }
   


        int pagamento = this->money;
        passageiro->pagar(pagamento);
        motorista->receber(pagamento);
        std::cout << passageiro->getName() << ":" << passageiro->getMoney() << " leave" << std::endl;
        this->passageiro = nullptr;
        this->money = 0;

    }
            std::string str() const {
            std::string motoristaStr = motorista ? motorista->str() : "None";
            std::string passageiroStr = passageiro ? passageiro->str() : "None";
            return fn::format("Cost: {}, Driver: {}, Passenger: {}", money, motoristaStr, passageiroStr);
        }
};

     
class Adapter {
    Uber uber;
public:
    void setDriver(std::string name, int money) {
        uber.setDriver(std::make_shared<Person>(name, money));
    }
    void setPass(std::string name, int money) {
        uber.setPass(std::make_shared<Person>(name, money));
    }
    void drive(int distance) {
        uber.drive(distance);
    }
    void leavePass() {
        uber.leavePass();
    }
    void show() {
          std::cout << uber.str() << std::endl;

    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}