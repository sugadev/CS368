#include <iostream>
#include <fstream>
#include<sstream>
#include<vector>
#include<map>
using namespace std;
#ifndef ARFFPARSER_H_
#define ARFFPARSER_H_
/*
 *  class for parsing the Arff Files
 *  @author sugadev chellakkannu
 */
class ArffParser {
private:
	ifstream file; //file handler to the input file
	map<int, vector<string> > featureMap; // map for the index feature mapping
public:
	/*
	 *  constructor that initializes the Arff parser with the give filename
	 *  @param name - name of the arff file
	 */
	ArffParser(string name);
	/*
	 *  Gets the features at the given index
	 *  @param index - index of the feature list
	 *  @return the features at the given index
	 */
	vector<string> getFeaturesAtIndex(int index);
	/*
	 * parses the header from the given arff file
	 */
	void parseHeaders();
	/*
	 * changes the arff file to the given file name
	 * @param name - name of the new arff file
	 */
	void initFile(string name);
	/*
	 * Gets the next input line from the arff file
	 * @return the features of the next line
	 */
	vector<string> getNext();
	/*
	 * Gets the classification classes
	 * @return the list of classes in the arff file
	 */
	vector<string> getClasses();
};

#endif /* ARFFPARSER_H_ */
