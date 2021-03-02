#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;		// array of character
	int size;			// size of strArray
	void strCpy (char* A, char* B, int n);
public:
	myString ();				// default constructor
	myString(char* inpStr);		// non-default constructor
	myString (myString& B);		// non-default constructor
	int Size();					// return size of array strArray
	char* getWord();			// return strArray
    bool operator == (myString& B);			// operator check if two myString object equal or not
    bool operator > (myString& B);			// operator check if a myString object greater than B or not
    bool operator < (myString& B);			// operator check if a myString object smaller than B or not
    myString& operator = (myString& B);		// assign myString object B to a myString object
    myString& operator = (char* B);			// assign char B to a myString object
};

// outputs a given string A. Return size of strArray
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')			// get the size of inpStr
		i++;
	size = i;
	strArray = new char[size];			// create new strArray with size is size
	emptyString (strArray, size+1);		// fill strArray with null element
	for (int j=0; j < size; j++)		// then assign all element of inpStr to strArray
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;			// assign size of B to size
	strArray = new char[size];			// create new strArray with size is size
	emptyString(strArray, size+1);		// fill strArray with null element
	stringCopy (B.strArray, size, strArray);	// copy all element in strArray of B to strArray
}

// Return strArray
char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
	int i = 0;
	while (B[i] != '\0')	// get the size of B character
		i++;
	size = i;
	strArray = new char[size];		// assign new strArray with size is size
	emptyString(strArray, size+1);	// fill strArray with null element
	for (int j = 0; j < size; j++)	// then assign all element of inpStr to strArray
		strArray[j] = B[j];

	return *this;					// return strArray, size of array
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
	if(strArray != NULL)		// If array is not null, delete it
			delete[] strArray;
	size = B.size;				// assign size of B to size
	strArray = new char[size];	// create new strArray with size is size
	emptyString(strArray, size+1);				// fill strArray with null elements
	stringCopy(B.strArray, size, strArray);		// copy all element in strArray of B to strArray

	return *this;				// return strArray, size of array
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {
	if (B.size == size){					// check if two size is equal or not
		for (int i = 0; i < size; i++){		// loop if is there any element is not equal, If so, return false
			if (B.strArray[i] != strArray[i])
				return false;
		}
	}
	else	// if two size is not equal, return false
		return false;
	return true;	// if size equal and each element of two object equal, return true

}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {
	int i = 0;	// index of strArray
	while (strArray[i] != '\0' || B.strArray[i] != '\0'){	// check if both element of are null or null. If both are null, exist loop
		// if strArray at index i is null while B.strArray is not
		// that mean strArray have small size and also mean all element before current index is equal to other strArray
		// Example: "not" is smaller than "notify".
		if (strArray[i] == '\0' && B.strArray[i] != '\0')
			return true;
		if (strArray[i] == B.strArray[i])		// If both are equal increment index i
			i++;
		else if (strArray[i] < B.strArray[i])	// If there is one index smaller, strArray smaller than B.strArray
			return true;
		else
			return false;	// else return false

	}
	return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {
	int i = 0;	// index of strArray
	while (strArray[i] != '\0' || B.strArray[i] != '\0'){	// check if both element of are null or null. If both are null, exist loop
		// if B.strArray at index i is null while strArray is not
		// that mean strArray have larger size and also mean all element before current index is equal to other strArray
		// Example: "notify" is greater than "not".
		if (strArray[i] != '\0' && B.strArray[i] == '\0')
			return true;
		if (strArray[i] == B.strArray[i])		// If both are equal increment index i
			i++;
		else if (strArray[i] > B.strArray[i])	// If there is one index lager, strArray larger than B.strArray
			return true;
		else
			return false;	// else return false

	}
	return false;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) {	// check if the file have read to the end
		cin.get(c);			// get character c
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) { 		// make sure c is not null or space
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) )
					str[i++] = c;	// if character is upper or lower case letter or number, add to str
			}
			else if ((c == '\n') && (i > 0))	// if c is null and c is not first character, just return str
				return str;
			else if ((c == ' ') && (i > 0))		// if c is space and c is not first character, just return str
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
	int binarySearchAndInsert (myString& W);
protected:
	myString* _words;		// myString object _words
	int* _frequencies;		// array _frequencies
	int _size;				// size of _words and _frequencies

public:
	bagOfWords ();			// default constructor
	bagOfWords (int numOfWords);	// non default constructor

	myString* get_Words();	// return _words
	int* get_Freq();		// return frequencies
	int get_size();			// return size of _words, _frequencies

	void setSize(int i);	// set the new size for _words, _frequencies

	void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortWords(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
	~bagOfWords();	//destructor
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
	_size = 0;
	_words = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
	_size = numOfWords;
	_words = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

// Return _words
myString* bagOfWords::get_Words()
{
	return _words;
}

// return _frequencies
int* bagOfWords::get_Freq()
{
	return _frequencies;
}

// return size of _words and _frequencies
int bagOfWords::get_size()
{
	return _size;
}

// set the new size for _words and _frequencies
void bagOfWords::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display()
{

	// TODO
	cout << "Bag of Words: " << _size << endl;
	for (int i = 0; i < _size; i++){
		cout << _words[i] << ": " << _frequencies[i] << endl;
	}

}

// sort the _words and _frequencies based on frequencies in ascending order
void bagOfWords::sortFreq()
{
	// TODO
	int temp1;			// temp int variable
	myString temp2;		// temp myString variable
	for (int i = 0; i < _size; i++){  		// take the element at certain index
		for (int j = i+1; j < _size; j++){	// then loop to compare with all element behind it
			if (_frequencies[i] > _frequencies[j]){		// if element at certain index of frequencies greater
				temp1 = _frequencies[i];				// than the next element, swap it
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = temp1;

				temp2 = _words[i];						// also swap the word  corresponding with frequencies
				_words[i] = _words[j];
				_words[j] = temp2;
			}
			if (_frequencies[i] == _frequencies[j]){	// If two element is equal, sort base on alphabetically
				if (_words[i] > _words[j]){				// swap the word to follow alphabetically order
					temp2 = _words[i];
					_words[i] = _words[j];
					_words[j] = temp2;

					temp1 = _frequencies[i];
					_frequencies[i] = _frequencies[j];	// swap frequencies corresponding with word
					_frequencies[j] = temp1;
				}
			}
		}
	}
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords()
{
	//char* temp;
	myString temp1;		// temp myString variable
	int temp2;			// temp int variable
;	for (int i = 0; i < _size; i++){		// take the element at certain index
		for (int j = i+1; j < _size; j++){	// then loop to compare with all element behind it
			if (_words[i] > _words[j]){		// if element at certain index of word greater
				temp1 = _words[i];			// than the next element, swap it
				_words[i] = _words[j];
				_words[j] = temp1;

				temp2 = _frequencies[i];
				_frequencies[i] = _frequencies[j];		// swap frequencies corresponding with word
				_frequencies[j] = temp2;
			}
		}
	}
}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{
	bagOfWords* newBag = new bagOfWords(this->get_size());	// create newBag with size is size of this _words
	for (int i = 0; i < newBag->_size; i++){
		newBag->_words[i] = _words[i];		// loop to copy all element of this _word to _words of newBag
		newBag->_frequencies[i] = _frequencies[i];	// copy all element of this _frequencies to _frequencies of newBag
	}

	int i = 0;
	while (i < numStopWords){ 	// loop in range of numStopWords
		for (int j = 0; j < newBag->_size; j++){	// loop each element in _words of newBag
			if (stopWords[i] == newBag->_words[j]){	// if the stopWord at index i is in _word, do the remove
				for (int k = j; k < newBag->_size - 1; k++){	// remove by shifting all the elements behind index need to remove
					newBag->_words[k] = newBag->_words[k + 1];	// to the left. So the element at that index will be removed
					newBag->_frequencies[k] = newBag->_frequencies[k + 1];	// also shift corresponding to the left
				}
				newBag->setSize(--newBag->_size);	// decrease the size of _words and _frequencies of newBag
			}
		}
		i++;
	}	// when done with looping, all the word in stopWordList has been remove from _words
	return newBag;	// return new bag
}

// to search for a given word in _words - returns index of element where will be inserted
int bagOfWords::binarySearchAndInsert (myString& wordToFind)
{
	int start = 0;			// start index
	int end = _size - 1 ;	// end index
	int mid;				// middle index

	while (start < end){	// while start index smaller than middle index
		mid = (start + end) / 2;
		if (_words[mid] == wordToFind){		// if element at mid equal wordToFind, return that index
			return mid;
		}

		else if (_words[mid] < wordToFind){		// if it is smaller, re-range start now is mid + 1
			start = mid + 1;
		}

		else{
			end = mid - 1;	//if it is greater, re-range end now is mid - 1
		}
	}

	// if start and end are equal and compare element at start with wordToFind. If it is smaller, return index next to start
	if ((start == end) && (_words[start] < wordToFind))
		return start + 1;
	// if start greater than end or element at start greater than wordToFind, return index start
	else
		return start;

}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
	// re-allocated _words and _frequencies by create new word with size is _size+1. With +1, array could contains
	// a null position after last index. It would help to shift element to the left when insert new word
	myString* tempWord = new myString[_size + 1];
	int* tempFre = new int[_size + 1];
	for (int i = 0; i < _size; i++){
		tempWord[i] = _words[i];		//copy all _word's element to tempWord
		tempFre[i] = _frequencies[i];	//copy all _frequencies's element to tempFre
	}

	int position = binarySearchAndInsert(newWord);	// assign index is returned in binarySearchAndInsert to position
	if (tempWord[position] == newWord){		// if tempWord contained newWord at position, increment frequency
		tempFre[position] = tempFre[position] + 1;
	}
	else {	// else shift all element to the left, start at position index
		for (int i = _size - 1; i >= position; i--){
			tempWord[i+1] = tempWord[i];
			tempFre[i+1] = tempFre[i];
		}
		tempWord[position] = newWord;	// after shifting, assign newWord to position
		tempFre[position] = 1;	//because this is first time the word is added to tempWord, frequency is 1
		this->setSize(++_size);	// increment size using setSize
	}
	_words = tempWord;	//assign tempWord back to _words
	_frequencies = tempFre;	//assign tempFre back to _frequencies

}

// destructor method. Delete the pointer data
// and set all static data to default
bagOfWords::~bagOfWords(){
	if (_words != NULL) delete _words;
	if (_frequencies != NULL) delete _frequencies;
	_size = 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

	int numStopWords;
	char* token;
	myString* tokenString;

    //read the first number from the file that contains the number of stop words
	cin >> numStopWords;
	cout << "Number of Stop words: " << numStopWords << endl;
	myString* stopWordsList = new myString[numStopWords];

	//read the stop words
	for (int i=0; i < numStopWords; i++)
	{
		token = getNextToken ();
		stopWordsList[i] = token; //calls the overloaded = operator on myString class
	}

	//Now read a text and put them in the bagOfWords instance.
	bagOfWords* myBag = new bagOfWords ();

	token = getNextToken();	// get the next token

	while (token != NULL)
	{
		tokenString = new myString (token); //create a myString object with the token
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();	// get the next token
	}

	// this should display the token and frequency;
	// note that becuase you are using binary search and insert the tokens will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*myBag).display ();

	(*myBag).sortFreq ();
	cout << endl;
	cout << "myBag - Sorted based on frequency:" << endl;
	(*myBag).display ();

	(*myBag).sortWords();
	cout << endl;
	cout << "myBag - Sorted alphabetically:" << endl;
	(*myBag).display ();

	bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
	cout << endl;
	cout << "newBag - Sorted alphabetically:" << endl;
	(*newBag).display();

	(*newBag).sortFreq ();
	cout << endl;
	cout << "newBag - Sorted based on frequency:" << endl;
	(*newBag).display ();

	// delete all the pointer data and object
	delete [] stopWordsList;
	delete myBag;
	delete newBag;
	delete tokenString;

	return 0;

}
