# CS368
NaiveBayes Classifier in CPP
	
	// STEP 0 : import the NAIVE BAYES class
	#include "NaiveBayes.h"

	// STEP 1: create an object for the NaiveBayes Classifier
	NaiveBayes nB;

	// STEP 2: start the training by providing the training file name
	nB.train("train1.arff");
	// HAPPY NEWS -- NAIVE BAYES MODEL IS READY NOW...

	//Time for prediction

	// STEP 3: Predict the label of the features !!!
	string predicted =  nB.predict(featureList);//featureList is vector<std::string>

	// STEP 4: Print the predicted feature
	cout<<"Predicted class = "<<predicted;

NOTE: sample demo is given in the ClassifierDemo.cpp 
