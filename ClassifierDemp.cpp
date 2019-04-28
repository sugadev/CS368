/*
 * ClassifierDemp.cpp
 *
 *  Created on: 27-Apr-2019
 *   @author: sugadev chellakkannu
 */


// STEP 0 : import the NAIVE BAYES class
#include "NaiveBayes.h"

/*
 * Main method that demonstrates the usage of the Classifier API
 */
int main() {

	//STEP 1: create an object for the NaiveBayes Classifier
	NaiveBayes nB;

	//STEP 2: start the training by providing the training file name
	nB.train("data/lymph_train.arff");
	// HAPPY NEWS -- NAIVE BAYES MODEL IS READY NOW...

	//Time for prediction

	// I've the data in a arff file thus using it. You can just pass the feature vector directly
	// STEP 4: create the arff parser for the test file
	ArffParser a("data/lymph_test.arff");

	//STEP 5: Predict the label of the first feature !!!
	string predicted =  nB.predict(a.getNext());

	//STEP 6: Print the predicted feature
	cout<<"Predicted class = "<<predicted;

	//loop through STEP 5 and STEP 6 to predice all the lines in the test data file

}





