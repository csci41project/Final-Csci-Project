//PROBLEM: WHEN I CREATED MAIN, I ONLY TOOK INTO CONSIDERATION USER DEFINING VARIABLES AND NOT DIRECT OPERATIONS
#include "class.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

int main(){ // ~*~ value not declared before? ~*~ //
	Calculator calc; //needed to create the calculator
	int value; // ~*~ Debugging... or trying to... string to int ~*~ //
	string input;
	getline(cin,input); //reads in entire string input
	stringstream parse(input); // ~*~ sstream to string stream ~*~ //

	while(parse){
		string a;
		parse >> a;
		if (!cin || cin.eof()) break; // ~*~ Has keyboard caught fire or reached end of file? 

		for (char& b : a) {
			cout << "First char input: " << b; //Testing... Delete later!
			a = toupper(b); // ~*~ Capitilizes all input ~*~ //
			cout << "To upper output: " << a; //Testing... Delete later!
		}
		if(a=="LET"){ //checks if user command is let. if yes, continues execution. if not, goes to else if statements. 
			char var; // ~*~ String to char ~*~ //
			string noperand;
			string set;
			if(set!="=") throw runtime_error("Must set equal to"); //checks for equal because it reads in as a string
			else continue;
			parse >> var;
			parse >> noperand; //this is where i got a bit confused with the operands and variable values
			parse >> value; //converts to int with ss here
			
			if(isalpha(var)){ //if the input is an alphabet, will set variable name  // ~*~ isalpha() can only be used with a character or an int ~*~ //
				calc.addvariable(var,value); // ~*~ Trying Calculator(var,value); ~*~ //
			}
			else  throw runtime_error("Invalid variable input");
			/*if(value >= numeric_limits<int>::max())  // ~*~ Figure out applications later... ~*~ // 
				throw runtime_error("Given variable is too large");  //~*~
			if(isdigit(value)){ //takes the user inputted value. because input is string, it converts to int.
				istringstream buffer(value);
				int val;
				buffer>>val; //these three lines were string to int conversion*/
				calc.addvariable(var, value); //but how do add the match value to the assigned variable??
		}
			//so i wasn't entirely sure about the operand part. i'm getting it mixed up with the value i know and so i've been confused sorting it out. 
		else if(a == "QUIT" || a == "Q") exit(EXIT_SUCCESS);
		else throw runtime_error("Invalid command. Must use 'LET' to define variable values");
	//	}
	}
	calc.domath(); //calls on math functions after user input check should go here
}
