import csv
import logging
import WineQualityMetrics

from sklearn.cluster import KMeans
from sklearn import preprocessing
from copy import deepcopy
from WineQualityMetrics import WineQualityMetricsEnum
from sklearn.linear_model import LogisticRegression
from collections import Counter

"""
Returns a list that contain the imported, from a csv file rows, as class instances

Attributes
    ----------
    fileName : str
        A string that contains the file path and the file name
        
    delimiter : str
        The delimiter used in the csv
        
    ignoredRows : list<int>
        A list containing the index of the csv file rows that will be ignored
"""
def CsvImporter(fileName, delimiter, ignoredRows):
    # Try to open the csv file
    try:
        with open(fileName) as csvFile:

            # Create a csv file reader to read the opened file
            csvFileReader = csv.reader(csvFile, delimiter = delimiter)

            # Initialize an index for the csv file lines
            csvLineIndex = 0

            # Initialize a list that will contain the class instances
            instanceList = []

            # For each row in the csv file...
            for csvFileRow in csvFileReader:

                # If the row has to be imported...
                if csvLineIndex not in ignoredRows:

                    # Create the class instance based on the imported row
                    classInstance = WineQualityMetrics.WineQualityMetrics(csvFileRow[0], csvFileRow[1], csvFileRow[2],
                                                                          csvFileRow[3], csvFileRow[4], csvFileRow[5],
                                                                          csvFileRow[6], csvFileRow[7], csvFileRow[8],
                                                                          csvFileRow[9], csvFileRow[10], csvFileRow[11])

                    # Add the class instance to the list
                    instanceList.append(classInstance)

                # Increase the csv line index
                csvLineIndex += 1

            # Return the imported class instances
            return instanceList

    # Catch the IOError
    except IOError:

        # Inform the user
        logging.exception("Csv file cannot be opened.")


"""
Returns a list that contain lists. Each subsequent list contains the selected properties of the class instances

Attributes
    ----------
    classList : list<object>
        The list that contain the class instances

    targetPropertyIndexList : list<int>
        The list that contains the indexes of the class attributes
"""
def ClassListToClassPropertiesList(classList, targetPropertyIndexList):

    # Initialise a list that will contain the class properties lists
    targetClassPropertiesList = []

    # For each class in the class list
    for instance in classList:

        # Get the class properties list
        propertyList = instance.ClassToClassPropertiesList()

        # Initialize an index for the properties
        propertyIndex = 0

        # Initialize a list that will contain the target property
        targetPropertyList = []

        # For every property...
        for classProperty in propertyList:

            # If the property is selected
            if propertyIndex in targetPropertyIndexList:

                # Add the property into the list
                targetPropertyList.append(classProperty)

            # Index the next property
            propertyIndex += 1

        # Append the target properties list
        targetClassPropertiesList.append(targetPropertyList)

    # Return the list that contain the target properties lists
    return targetClassPropertiesList


"""
Returns the SVM prediction, after removing the pH column from the training and test samples

Attributes
    ----------
    trainingSampleList : list<list<object>>
        The list that contains the training samples for the SVM

    trainingTargetSampleList : list<object>
        The list that contains the target training value samples for the SVM
        
    testSampleList : list<int>
        The list that contains the test value samples for the SVM
    
    supportVectorClassifier : SVM
        The support vector machine object
"""
def RemovePHColumn(trainingSampleList, trainingTargetSampleList, testSampleList, supportVectorClassifier):

    # Deep copy the training sample list to the removed pH training sample list
    removedPHTrainingSampleList = deepcopy(trainingSampleList)

    # Deep copy the test sample list to the removed pH test sample list
    removedPHTestSampleList = deepcopy(testSampleList)

    # For every training sample...
    for sampleList in removedPHTrainingSampleList:

        # Remove the ph values
        sampleList.pop(WineQualityMetricsEnum.pH.value)

    # For every training sample...
    for sampleList in removedPHTestSampleList:

        # Remove the ph values
        sampleList.pop(WineQualityMetricsEnum.pH.value)

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(removedPHTrainingSampleList, trainingTargetSampleList)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(removedPHTestSampleList)


"""
Returns the SVM prediction, after replacing one third of the pH column from the training samples, with the average pH of the rest of the training samples

Attributes
    ----------
    trainingSampleList : list<list<object>>
        The list that contains the training samples for the SVM

    trainingTargetSampleList : list<object>
        The list that contains the target training value samples for the SVM

    testSampleList : list<int>
        The list that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object
        
    editedTrainingSampleListLength : int
        The length of the one third of the training samples
"""
def AveragePHColumn(trainingSampleList, trainingTargetSampleList, testSampleList, supportVectorClassifier, editedTrainingSampleListLength):

    # Deep copy part of the training sample list to the average pH training sample list
    averagePHTrainingSampleList = deepcopy(trainingSampleList)

    # Initialise a sum to 0
    Average = 0

    # For every sample list in the non edited training sample list...
    for sampleList in averagePHTrainingSampleList[editedTrainingSampleListLength:]:

        # Add the pH value to the sum
        Average += sampleList[WineQualityMetricsEnum.pH.value]

    # Get the average pH in the non edited training sample list
    Average /= len(averagePHTrainingSampleList) - editedTrainingSampleListLength

    # For every edited test sample in the first one third of the list...
    for sampleList in averagePHTrainingSampleList[:editedTrainingSampleListLength]:

        # Remove the pH value
        sampleList[WineQualityMetricsEnum.pH.value] = Average

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(averagePHTrainingSampleList, trainingTargetSampleList)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(testSampleList)


"""
Returns the SVM prediction, after applying Logistic Regression to the pH column of the training samples

Attributes
    ----------
    trainingSampleList : list<list<object>>
        The list that contains the training samples for the SVM

    trainingTargetSampleList : list<object>
        The list that contains the target training value samples for the SVM

    testSampleList : list<int>
        The list that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object
        
    editedTrainingSampleListLength : int
        The length of the one third of the training samples
"""
def LogisticRegressionPHColumn(trainingSampleList, trainingTargetSampleList, testSampleList, supportVectorClassifier, editedTrainingSampleListLength):

    # Initialise a logistic regression object
    logisticRegression = LogisticRegression()

    # Deep copy part of the training sample list to the logistic regression training sample list
    logisticRegressionTrainingSampleList = deepcopy(trainingSampleList[editedTrainingSampleListLength:])

    # Deep copy part of the training sample list to the logistic regression test sample list
    logisticRegressionTestSampleList = deepcopy(trainingSampleList[:editedTrainingSampleListLength])

    # For every training sample...
    for sampleList in logisticRegressionTestSampleList:

        # Remove the pH values
        sampleList.pop(WineQualityMetricsEnum.pH.value)

    # Declare a training target sample list for the logistic regression
    logisticRegressionTrainingTargetSampleList = []

    # For every training sample...
    for sampleList in logisticRegressionTrainingSampleList:

        # Remove the pH values
        logisticRegressionTrainingTargetSampleList.append(sampleList.pop(WineQualityMetricsEnum.pH.value))

    # Initialise a label encoder
    labelEncoder = preprocessing.LabelEncoder()

    # Transform the continuous float values to mutliclass int values
    transformedTargetSamplesValues = labelEncoder.fit_transform(logisticRegressionTrainingTargetSampleList)

    # Fit the logisticRegression using the training sample lists
    logisticRegression.fit(logisticRegressionTrainingSampleList, transformedTargetSamplesValues)

    # Predict the target property values of the test sample set
    winePHPrediction = logisticRegression.predict(logisticRegressionTestSampleList)

    # Inverse transform the mutliclass int values to continuous float values
    winePHPrediction = labelEncoder.inverse_transform(winePHPrediction)

    # For every training sample...
    for index in range(len(trainingSampleList[:editedTrainingSampleListLength])):

        # Remove the pH values
        trainingSampleList[index][WineQualityMetricsEnum.pH.value] = winePHPrediction[index]

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(testSampleList)


"""
Returns the SVM prediction, after applying K-Means to the training samples and replacing the pH with average pH of the clustered samples

Attributes
    ----------
    trainingSampleList : list<list<object>>
        The list that contains the training samples for the SVM

    trainingTargetSampleList : list<object>
        The list that contains the target training value samples for the SVM

    testSampleList : list<int>
        The list that contains the test value samples for the SVM

    supportVectorClassifier : SVM
        The support vector machine object

    editedTrainingSampleListLength : int
        The length of the one third of the training samples
"""
def KMeansPHColumn(trainingSampleList, trainingTargetSampleList, testSampleList, supportVectorClassifier, editedTrainingSampleListLength):

    # Deep copy part of the training sample list to the logistic regression training sample list
    kMeansPHTrainingSampleList = deepcopy(trainingSampleList[editedTrainingSampleListLength:])

    # Deep copy part of the training sample list to the logistic regression test sample list
    kMeansPHTestSampleList = deepcopy(trainingSampleList[:editedTrainingSampleListLength])

    # For every training sample...
    for sampleList in kMeansPHTrainingSampleList:

        # Remove the pH values
        sampleList.pop(WineQualityMetricsEnum.pH.value)

    # For every training sample...
    for sampleList in kMeansPHTestSampleList:

        # Remove the pH values
        sampleList.pop(WineQualityMetricsEnum.pH.value)

    # Initialise the K-Means clustering object
    kMeansClustering = KMeans()

    # Fit the K-Means clustering object
    kMeansClustering.fit(kMeansPHTrainingSampleList)

    # Get the training sample clustering labels
    trainingSampleClusteringLabels = kMeansClustering.labels_

    # Predict the clusters of the samples that miss the pH value
    testSampleClusteringPrediction = kMeansClustering.predict(kMeansPHTestSampleList)

    # Declare a dictionary for the clusters and the average pH values
    ClusterPHDictionary = {}

    # For every K-Means cluster
    for index in range(kMeansClustering.n_clusters):

        # Set the cluster's average pH value to 0
        ClusterPHDictionary[index] = 0

    # For every clustering label...
    for index in range(len(trainingSampleClusteringLabels)):

        # Sum the pH values of the training samples that belong in the same cluster
        ClusterPHDictionary[trainingSampleClusteringLabels[index]] += kMeansPHTrainingSampleList[index][WineQualityMetricsEnum.pH.value]

    # Initialise a Counter object to count the number of samples that belong to each cluster
    clusterNumberOfOccurrencesCounter = Counter(trainingSampleClusteringLabels)

    # For every cluster...
    for clusterEntry in ClusterPHDictionary.keys():

        # Get the average pH of the samples that belong to the cluster
        ClusterPHDictionary[clusterEntry] /= clusterNumberOfOccurrencesCounter[clusterEntry]

    # For every edited test sample in the first one third of the list...
    for index in range(len(trainingSampleList[:editedTrainingSampleListLength])):

        # Update the pH value of the training sample
        trainingSampleList[index][WineQualityMetricsEnum.pH.value] = ClusterPHDictionary.get(testSampleClusteringPrediction[index])

    # Fit the supportVectorClassifier using the training sample lists
    supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

    # Predict the target property values of the test sample set
    return supportVectorClassifier.predict(testSampleList)
