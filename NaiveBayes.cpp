/*
 * NaiveBayes.cpp
 *
 *  Created on: 20-Apr-2019
 *  author: sugadev chellakkannu
 */

#include "NaiveBayes.h"
/**
 *	updates the count for the given class label
 *	@param label - label to increment the count
 */
void NaiveBayes::updatePYCount(string label) {
	if (pY.find(label) == pY.end())//new label in the training set
		pY[label] = 0;
	pY[label] += 1;
}
/**
 * updates the conditional probability count
 * @param label - class label
 * @param features - training data point features
 */
void NaiveBayes::updatePXGYCount(string label, vector<string> features) {
	vector<map<string, float> > pX;
	if (pXGY.find(label) != pXGY.end()) {//new feature value for the label
		pX = pXGY[label];
	}

	//training -- updating the probabilites based on the input features
	for (int i = 0; i < features.size() - 1; i++) {
		map<string, float> curFeatureSet;
		if (pX.size() > i)//feature index present
			curFeatureSet = pX.at(i);

		if (curFeatureSet.find(features.at(i)) == curFeatureSet.end()) {//feature value not found
			curFeatureSet[features.at(i)] = 0;
		}
		curFeatureSet[features.at(i)] = curFeatureSet[features.at(i)] + 1;
		if (pX.size() <= i)
			pX.push_back(curFeatureSet);
		pX[i] = curFeatureSet;//getting and setting as new to cpp!!!
	}
	pXGY[label] = pX;
}
/**
 * updates of the probabilies based on the given features
 * @param features - features on the training data point
 */
void NaiveBayes::updateProb(vector<string> features) {
	string label = features.at(features.size() - 1);
	updatePYCount(label); //update label count
	updatePXGYCount(label, features); // update conditional count

}
/**
 * divides the probabilites by the given size
 * @param n - size to divide the probabilities
 */
void NaiveBayes::divideN(int n) {
	for (map<string, float>::iterator it = pY.begin(); it != pY.end(); ++it) {
		string label = it->first;
		int count = it->second;
		vector<map<string, float> > pX = pXGY[label];
		for (int i = 0; i < numFeatures; i++) {
			map<string, float> features = pX.at(i);
			vector<string> valueList = parser->getFeaturesAtIndex(i);
			int numValues = valueList.size();
			for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
				if (features.find(valueList.at(valueIndex)) == features.end()) {//put 0 for all non found values in the training set
					features[valueList.at(valueIndex)] = 0;
				}
				features[valueList.at(valueIndex)] = (features[valueList.at(
						valueIndex)] + 1) / (count + numValues);// add pseudo counts of 1 for normalization
			}
			pX[i] = features;
		}
		pXGY[label] = pX;
		pY[label] = pY[label] + 1 / (n + parser->getClasses().size());// add pseudo counts of 1 for normalization
	}

}
/*
 * Trains the Naive Bayes classifier with the given training file
 * @param trainingFile - name of the training dataset file
 */
void NaiveBayes::train(string trainingFile) {
	parser = new ArffParser(trainingFile); // initialize the parser
	vector<string> features;
	trainingSetSize = 0;
	while (true) {
		features = (parser->getNext()); // get a data point
		if (features.size() == 0) //end of training set
			break;
		numFeatures = features.size() - 1; // number of features in the dataset
		trainingSetSize++;
		updateProb(features); //compute the probabilities
	}
	divideN(trainingSetSize); // compute the final probabilites
}
/**
 * calculate the conditional probabilities of the given features and class
 * @param label - the classification class
 * @param - features - list of features
 * @return the probability value
 */
float NaiveBayes::calcXGY(string label, vector<string> features) {
	float res = 1;
	vector<map<string, float> > pX = pXGY[label];
	for (int i = 0; i < numFeatures; i++) {
		map<string, float> featureProbGY = pX.at(i);
		if (featureProbGY.find(features.at(i)) == featureProbGY.end())
			res = 0; //no more needed due to normalization done earlier using pseudocounts of 1
		else
			res = res * featureProbGY[features.at(i)]; //update prob
	}
	return res;
}
/*
 * predicts the class of the given features
 * @param features - list of inference features
 * @return the predicted class
 */
string NaiveBayes::predict(vector<string> features) {
	vector<string> classes = parser->getClasses();
	string predictedLabel;
	float maxProb = 0;
	float denominator = 0;
	//calculate the denominator of the Naive Bayes probability calculation
	for (int i = 0; i < classes.size(); i++) {
		string label = classes.at(i);
		denominator = denominator + (pY[label] * calcXGY(label, features));

	}
	//calculate the denominator of the Naive Bayes probability calculation
	for (int i = 0; i < classes.size(); i++) {
		string label = classes.at(i);
		float numerator;
		numerator = pY[label] * calcXGY(label, features);
		float res = numerator / denominator;// probability for the current label
		if (res > maxProb) {//max probability for new label fount
			maxProb = res;
			predictedLabel = label;
		}
		cout << "Probability of "<<label << " = " << res << endl;
	}
	return predictedLabel;
}
