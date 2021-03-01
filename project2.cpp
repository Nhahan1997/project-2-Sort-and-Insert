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
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
};

// outputs a given string A
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
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}

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

	// TODO
	int i = 0;
	while (B[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString(strArray, size+1);
	for (int j = 0; j < size; j++)
		strArray[j] = B[j];

	return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {

	// TODO
	if(strArray != NULL)
			delete[] strArray;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy(B.strArray, size, strArray);

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	// TODO
	if (B.size == size){
		for (int i = 0; i < size; i++){
			if (B.strArray[i] != strArray[i])
				return false;
		}
	}
	else
		return false;
	return true;

}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	int i = 0;
	while (strArray[i] != '\0'){
		if (strArray[i] == B.strArray[i])
			i++;
		else if (strArray[i] < B.strArray[i])
			return true;
		else
			return false;

	}
	return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	// TODO
	int i = 0;
	while (strArray[i] != '\0'){
		if (strArray[i] == B.strArray[i])
			i++;
		else if (strArray[i] > B.strArray[i])
			return true;
		else
			return false;

	}
	return false;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		//if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) )
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		//}
	}
	if (i > 0) return str;
	else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
	int binarySearchAndInsert (myString& W);
protected:
	myString* _words;
	int* _frequencies;
	int _size;

public:
	bagOfWords ();
	bagOfWords (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortWords(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
	~bagOfWords();
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

myString* bagOfWords::get_Words()
{
	return _words;
}

int* bagOfWords::get_Freq()
{
	return _frequencies;
}

int bagOfWords::get_size()
{
	return _size;
}

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

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
	// TODO
	int temp1;
	myString temp2;
	for (int i = 0; i < _size; i++){
		for (int j = i+1; j < _size; j++){
			if (_frequencies[i] > _frequencies[j]){
				temp1 = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = temp1;

				temp2 = _words[i];
				_words[i] = _words[j];
				_words[j] = temp2;
			}
			if (_frequencies[i] == _frequencies[j]){
				if (_words[i] > _words[j]){
					temp2 = _words[i];
					_words[i] = _words[j];
					_words[j] = temp2;

					temp1 = _frequencies[i];
					_frequencies[i] = _frequencies[j];
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
	myString temp1;
	int temp2;
;	for (int i = 0; i < _size; i++){
		for (int j = i+1; j < _size; j++){
			if (_words[i] > _words[j]){
				temp1 = _words[i];
				_words[i] = _words[j];
				_words[j] = temp1;

				temp2 = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = temp2;
			}
		}
	}
}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{

	// TODO
	bagOfWords* newBag = new bagOfWords(this->get_size() + 1);
	for (int i = 0; i < newBag->_size; i++){
		newBag->_words[i] = _words[i];
		newBag->_frequencies[i] = _frequencies[i];
	}

	int i = 0;
	while (i < numStopWords){
		for (int j = 0; j < newBag->_size; j++){
			if (stopWords[i] == newBag->_words[j]){
				for (int k = j; k < newBag->_size - 1; k++){
					newBag->_words[k] = newBag->_words[k + 1];
					newBag->_frequencies[k] = newBag->_frequencies[k + 1];
				}
				newBag->setSize(--newBag->_size);
			}
		}
	}
	return newBag;
}

// to search for a given word in _words - returns 0 if not found, 1 if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind)
{

	// TODO
	int start = 0;
	int end = _size - 1 ;
	int mid;

	while (start < end){
		mid = (start + end) / 2;
		if (_words[mid] == wordToFind){
			return mid;
		}

		else if (_words[mid] < wordToFind){
			start = mid + 1;
		}

		else{
			end = mid -1;
		}
	}

	if ((start == end) && (_words[start] < wordToFind))
		return start + 1;
	else
		return start;

}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
	// TODO

	myString* word = new myString[_size + 1];
	int* fre = new int[_size + 1];
	for (int i = 0; i < _size; i++){
		word[i] = _words[i];
		fre[i] = _frequencies[i];
	}

	int position = binarySearchAndInsert(newWord);
	if (word[position] == newWord){
		fre[position] = fre[position] + 1;
	}
	else {
		for (int i = _size - 1; i >= position; i--){
			word[i+1] = word[i];
			fre[i+1] = fre[i];
		}
		word[position] = newWord;
		fre[position] = 1;
		this->setSize(++_size);
	}
	_words = word;
	_frequencies = fre;

}

bagOfWords::~bagOfWords(){
	if (_words != NULL) delete _words;
	if (_frequencies != NULL) delete _frequencies;
	cout << "bagOfWords object destroy!" << endl;
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

	token = getNextToken();

	while (token != NULL)
	{
		tokenString = new myString (token); //create a myString object with the token
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();
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

	// TODO : destructors
	delete [] stopWordsList;
	delete myBag;
	delete newBag;
	delete tokenString;

	return 0;

}
