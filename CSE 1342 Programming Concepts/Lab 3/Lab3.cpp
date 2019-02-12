#include <iostream>
#include <string>
using namespace std;

int GetNumOfNonWSCharacters(const string& usrStr) {
	int non_WS_characters = 0;
	for(int i = 0; i < usrStr.length(); i++){
		if(!isspace(usrStr[i])){
			non_WS_characters++;
		}
	}
	return non_WS_characters;
}

int GetNumOfWords(const string& usrStr) {
   int count=0;
   unsigned i;

   for (i = 1; i < usrStr.size(); ++i) {
      if (isspace(usrStr.at(i)) && !isspace(usrStr.at(i - 1))) {
         ++count;
      }
   }
   if (!isspace(usrStr.at(usrStr.size() - 1))) {
      ++count;
   }
   return count;
}

int FindText(const string& toFind,  string& usrStr) {
	int occurences = 0;
	int pos = 0;
	while(true){
		pos = usrStr.find(toFind, pos);
		if(pos != string::npos){
			pos++;
			occurences++;
		}
		else{
			break;
		}
	}
	return occurences;
}

void ReplaceExclamation(string& usrStr) {
	int pos = 0;
	while(true){
		pos = usrStr.find("!", pos);
		if(pos != string::npos){
			usrStr.replace(pos, 1, ".");
			pos++;
		}
		else{
			break;
		}
	}
}

void ShortenSpace(string& usrStr) {
   unsigned i;
   string tmp;

   for (i = 1; i < usrStr.size(); ++i) {
      if (!(isspace(usrStr.at(i)) && isspace(usrStr.at(i - 1)))) {
         tmp = tmp + usrStr.at(i - 1);
      }

      if (i == usrStr.size() - 1) {
         tmp = tmp + usrStr.at(i);
      }
   }
   usrStr = tmp;
   return;
}

char PrintMenu(string& usrStr) {
   char menuOp = ' ';
   string toFind;
   int numFinds;

   cout << "MENU" << endl;
   cout << "c - Number of non-whitespace characters" << endl;
   cout << "w - Number of words" << endl;
   cout << "f - Find text" << endl;
   cout << "r - Replace all !\'s" << endl;
   cout << "s - Shorten spaces" << endl;
   cout << "q - Quit" << endl << endl;

   menuOp = ' ';

   while (menuOp != 'c' && menuOp != 'w' && menuOp != 'f' &&
         menuOp != 'r' && menuOp != 's' && menuOp != 'o' &&
         menuOp != 'q') {
      cout << "Choose an option:" << endl;
      cin >> menuOp;
   }

   if (menuOp == 'c') {
      cout << "Number of non-whitespace characters: " << GetNumOfNonWSCharacters(usrStr) << endl
      << endl;
      menuOp = ' ';
   }
   else if (menuOp == 'w') {
      cout << "Number of words: " << GetNumOfWords(usrStr) << endl << endl;
      menuOp = ' ';
   }
   else if (menuOp == 'f') {
      cin.ignore();
      cout << "Enter a word or phrase to be found:" << endl;
      getline(cin, toFind);

      numFinds = FindText(toFind, usrStr);

      cout << "\"" << toFind << "\"" << " instances: "
      << numFinds << endl << endl;
      menuOp = ' ';
   }
   else if (menuOp == 'r') {
      ReplaceExclamation(usrStr);
      cout << "Edited text: " << usrStr << endl << endl;
      menuOp = ' ';
   }
   else if (menuOp == 's') {
      ShortenSpace(usrStr);
      cout << "Edited text: " << usrStr << endl << endl;
      menuOp = ' ';
   }
   return menuOp;
}

int main() {
   string userString;
   char menuChoice = ' ';

   cout << "Enter a sample text:" << endl;
   getline(cin, userString);
   cout << endl;

   cout << "You entered: " << userString << endl << endl;

   while (menuChoice != 'q') {
      menuChoice = PrintMenu(userString);
   }
   return 0;
}
