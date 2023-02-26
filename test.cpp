#include"lexer/Lexer.cpp"
#include<iostream>
#include<iomanip>

using namespace std;

char out_buffer[64*1024] = {0};			// »º³åÇø 

int main() {
	freopen("script.is", "r", stdin);
	freopen("script.ilex", "w", stdout);
	
	setvbuf(stdout, out_buffer, _IOFBF, 512*1024); 

	string input_string;
	vector<Token> tokens;

	string tmp = "";
	while(getline(cin,tmp)) {
		input_string += (tmp+"\n");
	}

	Lexer lexer(input_string);
	tokens = lexer.parse();

	for(int i=0; i<tokens.size(); i++) {
		cout<<setiosflags(ios::left)<<setw(16)<<"<" + tokens[i].IDtoString() + ">"<<tokens[i].getText()<<endl;
	}
	
	fflush(stdout);

	return 0;
}
