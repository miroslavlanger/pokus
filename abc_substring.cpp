// FiniteAutomaton.cpp : does input string contain substring "abc"?
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	string input;
	int state = 0;
	cout << "Zadej vstupni retezec:";
	cin >> input;
	for (int i = 0; i <= input.length() - 1; i++) {
		switch (state) {
			case 0: switch (input[i]) {
						case 'a':	state = 1;
									break;
						default:	state = 0;
									break;
					};
					break;
			case 1:	switch (input[i]) {
						case 'a':	state = 1;
									break;
						case 'b':	state = 2;
									break;
						default:	state = 0;
									break;
					};
					break;
			case 2:	switch (input[i]) {
						case 'c':	state = 3;
									break;
						case 'a':	state = 1;
									break;
						default:	state = 0;
									break;
					};
					break;
			case 3:	switch (input[i]) {
						default:	state = 3;
									break;
					};
					break;
			default: state = 4;
		};
	};
	cout << endl << "Skoncil jsem ve stavu: " << state << endl;

	return 0;
}


