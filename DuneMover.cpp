/*****************************************************************************
// File Name : DuneMover.cs
// Author : Craig Hughes
// Creation Date : June 06, 2024
// Brief Description : This program is a tool that calculates the number of 
// tickets that have to be sold in a set number of operating hours to reach
// a certain price threshold
*****************************************************************************/
#include<iostream>
#include <iomanip>
#include<vector>
#include <string.h>
#include <string>
#include <cmath>

using namespace std;

bool check_float(string str);
bool check_int(string str);
void convertStringToFloat(string message, float &var);
void convertStringToInt(string message, int &var);
void RunCalculations(int goalValue, vector<float> prices, float duration, int passengerCount, int activeBuggies, vector<int> passengerSetup);
int Sum_Vector_Int(vector<int> vec);
float Sum_Vector_Float(vector<float> vec);


const string DIVIDER = "\n----------------------------------------------------------------------------------------------------------------------------------------------------\n";

int main(){

float desiredIntake,duration,nextVal,costOffset;

int passengerCount,totalPrices,buggyCount;

vector<float> prices;

vector<int> passengerMakeup;
//how many prices there are

cout << "\n\n WELCOME TO DUNE MOVER 2024\n\n" << endl;
convertStringToFloat("\n How much money do you want to make? ",desiredIntake);
convertStringToFloat("\n What are the cost of operations that you are trying to offset? ",costOffset);
convertStringToFloat("\n What is the anticipated duration of a dune ride in hours?" ,duration);
convertStringToInt("\n How many passengers can fit in a dune buggy? ",passengerCount);
convertStringToInt("\n How many dune buggies are operational? ",buggyCount);
convertStringToInt("\n How many different ticket prices are there?",totalPrices);

for(int i = 0; i < totalPrices; i++)
{
    convertStringToFloat("\n What is price " + to_string(i + 1) + "? " ,nextVal);
    prices.push_back(nextVal);
    cout << endl;
    convertStringToFloat("\n How many of " + to_string(i + 1) + " will be in a buggy? " ,nextVal);
    
    while(Sum_Vector_Int(passengerMakeup) + nextVal > passengerCount){
        convertStringToFloat("\n" + to_string((int)nextVal) + " Goes over buggy capacity. Try again. " ,nextVal);
    }

    passengerMakeup.push_back((int)nextVal);

}



//run calculations
RunCalculations(desiredIntake + costOffset,prices,duration,passengerCount,buggyCount,passengerMakeup);
//save values
return 0;
}


void RunCalculations(int goalValue, vector<float> prices, float duration, int passengerCount, int activeBuggies, vector<int> passengerSetup){
int ticketsNeeded;
int multipliedTickets; 
float carSum;

    cout << setprecision(2) << endl;

    //exaggerated simulation O(N)
    for(float i : prices)
    {
        ticketsNeeded =ceilf(goalValue/i);
    	cout<< DIVIDER <<"It would take " << to_string(ticketsNeeded) << " tickets worth $" << to_string(i) << 
        " to reach your goal. \nThis would take " <<  to_string(ceilf(ticketsNeeded/ passengerCount))  << " full buggy rides to sell this many tickets"
        << "\nIt would take " <<  to_string(ceilf((((ticketsNeeded/ passengerCount)*duration)/activeBuggies))) << " Hours to complete this with " << to_string(activeBuggies) << " active buggies." << endl;
    }

    //equal simulations 
    //O(N)
    carSum = Sum_Vector_Float(prices);
    ticketsNeeded = ceilf(goalValue / carSum);
    multipliedTickets = prices.size() * ticketsNeeded;
    cout<< DIVIDER <<"It would take " << to_string(ticketsNeeded) << " of each ticket to reach your goal. \n This would take " << to_string(ceilf(multipliedTickets/ passengerCount))  << " full buggy rides to sell this many tickets."
        << "\nIt would take " <<  to_string(ceilf((((multipliedTickets/ passengerCount)*duration)/activeBuggies))) << " Hours to complete this with " << to_string(activeBuggies) << " active buggies." << endl;
    

    //projected car makeup 
    //ticketsNeeded = ceilf();
    carSum = 0;
    for(int i = 0; i < prices.size();i++){
        carSum += prices[i] * passengerSetup[i];
    }
    cout << DIVIDER <<"One car with your projected setup will make $" << to_string(carSum) << ".\nIt would take "<< to_string(ceilf(goalValue/carSum)) << 
    " full buggy rides to reach your goal.\n" << "It would take " << to_string(ceilf(((goalValue/carSum) * duration)/activeBuggies))<< " hours to reach your goal with this setup and " <<
     to_string(activeBuggies) << " active buggies." << endl;

}


#pragma region Converters
void convertStringToFloat(string message, float &var){
    string input;
    cout << message;
    cin >> input;
    while(!check_float(input)){
        cout << "Invalid input. Please try again ";
        cin >> input;
    }
    var = stof(input);
} 
void convertStringToInt(string message, int &var){
    string input;
    cout << message;
    cin >> input;
    while(!check_int(input)){
        cout << "Invalid input. Please try again ";
        cin >> input;
    }
    var = stoi(input);
} 

#pragma endregion

#pragma region Checkers

bool check_float(string str) {
   bool foundDecimal = false;
   for (int i = 0; i < str.length(); i++){
      //check for decimal
      if(str[i] == '.' && !foundDecimal){
            foundDecimal = true;
       }
       else if(str[i] == '.' && foundDecimal) {
        return false;}
       //check for digit
      if (isdigit(str[i]) == false && str[i] != '.'){
        return false;
      }
   }
   return true;
}


bool check_int(string str){
    for (int i = 0; i < str.length(); i++){
       //check for digit
      if (isdigit(str[i]) == false)
            return false;
   }
   return true;
}

int Sum_Vector_Int(vector<int> vec){
    int sum = 0;
        for(int i : vec){
        sum += i;
    }
    return sum;
}

float Sum_Vector_Float(vector<float> vec){
    float sum = 0;
        for(float i : vec){
        sum += i;
    }
    return sum;
}
#pragma endregion