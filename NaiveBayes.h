#ifndef NAIVEBAYES_H_
#define NAIVEBAYES_H_
#include<vector>
#include<map>
#include<string>
#include "ArffParser.h"
using namespace std;
/**
 *
 * Class that implements the Nayes Bayes algorithm
 * @author sugadev chellakkannu
 */
class NaiveBayes {
private:
	ArffParser *parser;// input file parser
	vector<int> classes; //classification classes
	map<string,float> pY; //probability of the classes
	int numFeatures; // number of features in the dataset
	map<string, vector<map<string, float> > > pXGY; //conditional probabilities
	int trainingSetSize; // length of the training data
	/**
	 * divides the probabilites by the given size
	 * @param n - size to divide the probabilities
	 */
	void divideN(int n);
	/**
	 *	updates the count for the given class label
	 *	@param label - label to increment the count
	 */
	void updatePYCount(string label);
	/**
	 * updates the conditional probability count
	 * @param label - class label
	 * @param features - training data point features
	 */
	void updatePXGYCount(string label,vector<string> features);
	/**
	 * updates of the probabilies based on the given features
	 * @param features - features on the training data point
	 */
	void updateProb(vector<string> features);
	/**
	 * calculate the conditional probabilities of the given features and class
	 * @param label - the classification class
	 * @param - features - list of features
	 * @return the probability value
	 */
	float calcXGY(string label,vector<string> features);
public:
	/*
	 * Trains the Naive Bayes classifier with the given training file
	 * @param trainingFile - name of the training dataset file
	 */
	void train(string trainingFile);
	/*
	 * predicts the class of the given features
	 * @param features - list of inference features
	 * @return the predicted class
	 */
	string predict(vector<string> features);
};

#endif /* NAIVEBAYES_H_ */
