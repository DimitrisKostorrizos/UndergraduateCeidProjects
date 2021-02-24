from sklearn.cluster import KMeans
from sklearn import preprocessing
from copy import deepcopy
from sklearn.linear_model import LogisticRegression
from collections import Counter

"""
Returns the SVM prediction, after removing the pH column from the training and test samples

Attributes
    ----------
    trainingSample : DataFrame
        The DataFrame that contains the training samples for the SVM

    qualityTrainingSample : DataFrame
        The DataFrame that contains the target training value samples for the SVM
        
    testSample : DataFrame
        The DataFrame that contains the test value samples for the SVM
    
    supportVectorClassifier : SVM
        The support vector machine object
"""
def RemovePHColumn(trainingSample, qualityTrainingSample, testSample, supportVectorClassifier):

    # Get the training sample without the pH column
    removedPHTrainingSample = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]]

    # Get the test sample without the pH column
    removedPHTestSample = testSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]]
    
    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(removedPHTrainingSample, qualityTrainingSample)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(removedPHTestSample)


"""
Returns the SVM prediction, after replacing one third of the pH column from the training samples, with the average pH of the rest of the training samples

Attributes
    ----------
    trainingSample : DataFrame
        The DataFrame that contains the training samples for the SVM

    qualityTrainingSample : DataFrame
        The DataFrame that contains the target training value samples for the SVM

    testSample : DataFrame
        The DataFrame that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object
        
    editedTrainingSampleLength : int
        The length of the one third of the training samples
"""
def AveragePHColumn(trainingSample, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength):

    # Deep copy the training sample list to the average pH training sample
    averagePHTrainingSample = deepcopy(trainingSample)

    # Initialise a sum to 0
    Average = 0

    # For every sample list in the non edited training sample list...
    for sample in averagePHTrainingSample["pH"][editedTrainingSampleLength:]:

        # Add the pH value to the sum
        Average += sample

    # Get the average pH in the non edited training sample list
    Average /= len(averagePHTrainingSample) - editedTrainingSampleLength

    # For every edited test sample in the first one third of the list...
    for sample in averagePHTrainingSample["pH"][:editedTrainingSampleLength]:

        # Remove the pH value
        sample = Average

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(averagePHTrainingSample, qualityTrainingSample)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(testSample)


"""
Returns the SVM prediction, after applying Logistic Regression to the pH column of the training samples

Attributes
    ----------
    trainingSample : DataFrame
        The DataFrame that contains the training samples for the SVM

    qualityTrainingSample : DataFrame
        The DataFrame that contains the target training value samples for the SVM

    testSample : DataFrame
        The DataFrame that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object
        
    editedTrainingSampleLength : int
        The length of the one third of the training samples
"""
def LogisticRegressionPHColumn(trainingSample, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength):

    # Deep copy  the training sample list to the average pH training sample list
    logisticRegressionPHTrainingSample = deepcopy(trainingSample)

    # Initialise a logistic regression classifier object
    logisticRegressionClassifier = LogisticRegression(solver="liblinear")

    # Deep copy part of the training sample list to the logistic regression training sample list
    logisticRegressionTrainingSample = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]][editedTrainingSampleLength:]

    # Deep copy part of the training sample list to the logistic regression test sample list
    logisticRegressionTestSample = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]][:editedTrainingSampleLength]

    # Declare a training target sample list for the logistic regression
    logisticRegressionTrainingTargetSampleList = trainingSample["pH"][editedTrainingSampleLength:]

    # Initialise a label encoder
    labelEncoder = preprocessing.LabelEncoder()

    # Transform the continuous float values to multi-class int values
    transformedTargetSamplesValues = labelEncoder.fit_transform(logisticRegressionTrainingTargetSampleList)

    # Fit the logisticRegression using the training sample
    logisticRegressionClassifier.fit(logisticRegressionTrainingSample, transformedTargetSamplesValues)

    # Predict the target property values of the test sample
    winePHPrediction = logisticRegressionClassifier.predict(logisticRegressionTestSample)

    # Inverse transform the multi-class int values to continuous float values
    winePHPrediction = labelEncoder.inverse_transform(winePHPrediction)

    # For every training sample...
    for index in range(len(logisticRegressionPHTrainingSample["pH"][:editedTrainingSampleLength])):

        # Remove the pH values
        logisticRegressionPHTrainingSample[index] = winePHPrediction[index]

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(trainingSample, qualityTrainingSample)

    # Predict the target property values of the test sample
    return supportVectorClassifier.predict(testSample)


"""
Returns the SVM prediction, after applying K-Means to the training samples and replacing the pH with average pH of the clustered samples

Attributes
    ----------
    trainingSample : DataFrame
        The DataFrame that contains the training samples for the SVM

    qualityTrainingSample : DataFrame
        The DataFrame that contains the target training value samples for the SVM

    testSample : DataFrame
        The DataFrame that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object

    editedTrainingSampleLength : int
        The length of the one third of the training samples
"""
def KMeansPHColumn(trainingSample, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength):

    # Deep copy part of the training sample to the logistic regression training sample
    kMeansPHTrainingSample = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]][editedTrainingSampleLength:]

    # Deep copy part of the training sample to the logistic regression test sample
    kMeansPHTestSample = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "sulphates", "alcohol"]][:editedTrainingSampleLength]

    # Initialise the K-Means clustering object
    kMeansClustering = KMeans()

    # Fit the K-Means clustering object
    kMeansClustering.fit(kMeansPHTrainingSample)

    # Get the training sample clustering labels
    trainingSampleClusteringLabels = kMeansClustering.labels_

    # Predict the clusters of the samples that miss the pH value
    testSampleClusteringPrediction = kMeansClustering.predict(kMeansPHTestSample)

    # Declare a dictionary for the clusters and the average pH values
    ClusterPHDictionary = {}

    # For every K-Means cluster
    for index in range(kMeansClustering.n_clusters):

        # Set the cluster's average pH value to 0
        ClusterPHDictionary[index] = 0

    # For every clustering label...
    for index in range(len(trainingSampleClusteringLabels)):

        # Sum the pH values of the training samples that belong in the same cluster
        ClusterPHDictionary[trainingSampleClusteringLabels[index]] += trainingSample.iloc[index, 8]

    # Initialise a Counter object to count the number of samples that belong to each cluster
    clusterNumberOfOccurrencesCounter = Counter(trainingSampleClusteringLabels)

    # For every cluster...
    for clusterEntry in ClusterPHDictionary.keys():

        # Get the average pH of the samples that belong to the cluster
        ClusterPHDictionary[clusterEntry] /= clusterNumberOfOccurrencesCounter[clusterEntry]

    # For every edited test sample in the first one third of the DataFrame...
    for index in range(len(trainingSample[:editedTrainingSampleLength])):

        # Update the pH value of the training sample
        trainingSample.iloc[index, 8] = ClusterPHDictionary.get(testSampleClusteringPrediction[index])

    # Fit the supportVectorClassifier using the training sample
    supportVectorClassifier.fit(trainingSample, qualityTrainingSample)

    # Predict the target property values of the test sample
    return supportVectorClassifier.predict(testSample)
