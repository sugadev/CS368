/*
 * ArffParser.cpp
 *
 *  Created on: 19-Apr-2019
 *  author: sugadev chellakkannu
 */

#include "ArffParser.h"

/*
 *  constructor that initializes the Arff parser with the give filename
 *  @param name - name of the arff file
 */
ArffParser::ArffParser(string name) {
	file.open(name);
	if (!file.is_open()) { //error in opening file
		cout << "unable to open file";
		return;
	}
	//parse the headers
	parseHeaders();
}
/*
 * changes the arff file to the given file name
 * @param name - name of the new arff file
 */
void ArffParser::initFile(string name) {
	file.open(name); //point to the new file
	if (!file.is_open()) { //error in opening file
		cout << "unable to open file";
		return;
	}
	//parse the headers
	parseHeaders();
}

/*
 * Gets the next input line from the arff file
 * @return the features of the next line
 */
vector<string> ArffParser::getNext() {
	string line, token;
	vector<string> features;
	bool linePresent = false;
	while (getline(file, line)) {
		if (line.length() == 0) //skip empty line
			continue;
		char c = line[0];
		if (c != ' ') { // non blank line found
			linePresent = true;
			break;
		}
	}
	if (linePresent) { //next valid line is present
		istringstream ss(line);
		int index = 0;
		while (getline(ss, token, ',')) { //split using ',' and add to the features
			vector<string> feature_list = featureMap[index];
			features.push_back(token);
			featureMap[index] = feature_list;
			index++;
		}
	}
	return features;
}
/*
 *  Gets the features at the given index
 *  @param index - index of the feature list
 *  @return the features at the given index
 */
vector<string> ArffParser::getFeaturesAtIndex(int index) {
	return featureMap[index];
}
/*
 * Gets the classification classes
 * @return the list of classes in the arff file
 */
vector<string> ArffParser::getClasses() {
	//class is at the last index in the input file
	int classIndex = featureMap.size();
	return featureMap[classIndex - 1];
}

/*
 * parses the header from the given arff file
 */
void ArffParser::parseHeaders() {
	string line, token;
	int feature = 0;
	while (getline(file, line)) {
		if (line.length() == 0) { //skip empty line
			continue;
		}
		char c = line[0];
		if (c == ' ') //skip blank link
			continue;
		if (c == '@') {
			if (line[1] == 'r') //skip relation
				continue;
			if (line[1] == 'd') //break for data section
				break;
			string head = line.substr(line.find('{') + 1); //get the feature value list
			head = head.substr(0, head.size() - 1);
			head.erase(remove(head.begin(), head.end(), ' '), head.end());
			vector<string> feature_list;
			istringstream fv(head);
			//store the possible values in the feature vector map
			while (getline(fv, token, ',')) {
				feature_list.push_back(token);
			}
			featureMap[feature] = feature_list;
			feature++;
		}
	}
}
