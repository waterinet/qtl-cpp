#include <iostream>
#include "strings.h"

using namespace std;
using namespace qtl;

void SplitTest(const string& s, const string& c);

int main() {
	cout << "--------------------" << endl;
	SplitTest("", "/");
	cout << "--------------------" << endl;
	SplitTest("http://www.baidu.com/?key=value#page1", "");
	cout << "--------------------" << endl;
	SplitTest("", "");
	cout << "--------------------" << endl;
	SplitTest("http://www.baidu.com/?key=value#page1", "//");
	cout << "--------------------" << endl;
	SplitTest("http://www.baidu.com/?key=value#page1", "#");
	cout << "--------------------" << endl;
	SplitTest("http://www.baidu.com/?key=value#page1", "##");
}

void SplitTest(const string& s, const string& c) {
	cout << "s: " << s << endl;
	cout << "c: " << c << endl;
    string a, b;
    strings::Split(s, a, b, c); 
    cout << "[" << a << "][" << b << "]" << endl;
    
    strings::Split(s, a, b, c, true);
    cout << "[" << a << "][" << b << "]" << endl;
}
