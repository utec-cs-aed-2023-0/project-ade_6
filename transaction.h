#include <ctime>
#include <iostream>


#include <iostream>
using namespace std;

struct transaction
{
    string amount;
    string senderkey;
    string reciverkey;
    string timestamp;
    transaction(){}

    transaction(double amt, string sender, string reciever, time_t time) {
        amount = to_string (amt);
        senderkey = sender;
        reciverkey = reciever;
        timestamp = ctime(&time);
    }
    string get_data() {
        string result = "";
        result += this->amount;
        result += this->senderkey;
        result += this->reciverkey;
        result += this->timestamp;
        return result;
    }
};

