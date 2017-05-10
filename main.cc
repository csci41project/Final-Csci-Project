#include "class.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

int main(){

string input;
getline(cin,input); //reads in entire string input
sstream parse(input);

while(input){
	string a;
	cin>>a;
	if(a=="LET"){ //checks if user command is let. if yes, continues execution. if not, goes to else if statements. 
		string var;
		string noperand;
		string set;
		if(set!="=") throw runtime_error("Must set equal to"); //checks for equal because it reads in as a string
		else continue;
		cin>>var;
		cin>>noperand; //this is where i got a bit confused with the operands and variable values
		if(var.isalpha()){ //if the input is an alphabet, will set variable name
			addvariable(var,value);
		}
		else  throw runtime_error("Invalid variable input");
		cin>>value;
		if(value.isdigit()){ //takes the user inputted value. because input is string, it converts to int.
			istringstream buffer(value);
			int val;
			buffer>>val; //these three lines were string to int conversion
			addvariable(var, value) //but how do add the match value to the assigned variable??
	}
//so i wasn't entirely sure about the operand part. i'm getting it mixed up with the value i know and so i've been confused sorting it out. 
	else if(a=="QUIT") exit(EXIT_SUCCESS);
	else throw runtime_error("Invalid command. Must use "LET" to define variable values");
	}
}
domath(); //calls on math functions after user input check shoudl go here
