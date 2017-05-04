#include <vector>
enum Opcode{PLUS, MINUS, MODULUS, MULTIPLY, DIVIDE};
class IntCharPair {
	public:
		int value;
		const char variable;
		IntCharPair(char nvar, int nvalue):value(nvalue), variable(nvar){}
};
bool uniquevar(IntCharPair rhs, IntCharPair lhs){
	return (rhs.variable == lhs.variable);
}
class Calculator {
	public:
		vector <IntCharPair> variables;
		int rhs, lhs;
		Opcode op;
		void incodeop (char c){
			if (c == '+') op = PLUS; 
			if (c == '-') op = MINUS;
			if (c == 'x') op = MODULUS;
			if (c == '/') op = MULTIPLY;
			if (c == '%') op = DIVIDE;
		}
		void addvariable(int value, char var){
			variables.push_back(var,value);
			auto it = unique(variables.begin(),variables.end(),uniquevar);
			if (it != variables.end()) die();
		}
		int getvariable(char var){
			for (IntCharPair& i : variables){
				if (i.variable == var){
					return i.value++;
				}
			}
		}
		int domath(){
			switch (op){
				case PLUS: return addstuff();
				case MINUS: return substuff();
				case MODULUS: return modstuff();
				case MULTIPLY: return multstuff();
				case DIVIDE: return divstuff();
			}
			throw
		}
};
