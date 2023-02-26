#include"lexer/Lexer.cpp"
#include<iostream>
#include<iomanip>

using namespace std;

char out_buffer[64*1024] = {0};			// 缓冲区 

int main() {
	freopen("script.is", "r", stdin);
	freopen("script.ilex", "w", stdout);
	
	setvbuf(stdout, out_buffer, _IOFBF, 512*1024); 

	string input_string;
	vector<Token> tokens;

	string tmp = "";
	while(getline(cin,tmp)) {
		//这里的顺序不能调换
		//一旦调换，"!"也被加入input_string
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
