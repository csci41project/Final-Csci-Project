#include "class.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

int main(){ // ~*~ value not declared before? ~*~ //
try{
	Calculator calc; //needed to create the calculator
	int value; // ~*~ Debugging... or trying to... string to int ~*~ //
	string input;
	getline(cin,input); //reads in entire string input
	stringstream parse(input); // ~*~ sstream to string stream ~*~ //

	while(parse){
		string a;
		parse >> a;
		if (!cin || cin.eof()) break; // ~*~ Has keyboard caught fire or reached end of file? 

		for (char& b : a) b = toupper(b); // ~*~ Capitilizes all input ~*~ //
			char var; // ~*~ String to char ~*~ //
		if (a == "LET"){ //checks if user command is let. if yes, continues execution. if not, goes to else if statements. 
			string noperand;
			string set;
			parse >> var;
			parse >> noperand; //this is where i got a bit confused with the operands and variable values
			if(noperand!="="){
				cout << "Must set variable equal to something" << endl;	
				throw runtime_error("Must set equal to"); //checks for equal because it reads in as a string
			}
		parse >> value; //converts to int with ss here
			
			if(isalpha(var)){ //if the input is an alphabet, will set variable name  // ~*~ isalpha() can only be used with a character or an int ~*~ //
				calc.addvariable(var,value); // ~*~ Trying Calculator(var,value); ~*~ //
			}
			else  {
				cout << "Invalid variable input" << endl;
				throw runtime_error("Invalid variable input");
			}
			//if(isdigit(value)){ //takes the user inputted value. because input is string, it converts to int.
			//	istringstream buffer(value);
			//	int val;
			//	buffer>>val; //these three lines were string to int conversion*/
		//		calc.addvariable(var, value); //but how do add the match value to the assigned variable??
		}	
			//so i wasn't entirely sure about the operand part. i'm getting it mixed up with the value i know and so i've been confused sorting it out. 
		else if (a == "QUIT" || a == "Q") exit(EXIT_SUCCESS);
		else if (a != "QUIT" && a != "Q" && a != "LET"){
			cout << "Invalid command. Must say 'LET' to define" << endl;
			throw runtime_error("Invalid command. Must use 'LET' to define variable values");
		}
	}
	calc.domath(); //calls on math functions after user input check should go here
}
catch(...) { cout << "BAD INPUT" << endl;}
}
