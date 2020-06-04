import random

from sklearn.model_selection import StratifiedKFold, GridSearchCV

import HelperMethods
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import f1_score, precision_score
from sklearn.metrics import recall_score
from sklearn.svm import SVC
from WineQualityMetrics import WineQualityMetricsEnum
import numpy

# Initialise the list that contains the rows that will be ignored during the import
ignoredRowsList = [0]

# Import the wine quality metrics from the csv file
wineQualityMetricsInstanceList = HelperMethods.CsvImporter(
    "Project Εξόρυξη Δεδομένων και Αλγόριθμοι Μάθησης/winequality-red.csv", ",", ignoredRowsList)

# Get the imported instances count
importedInstancesSize = len(wineQualityMetricsInstanceList)

# Calculate the size of the test sample
testSampleLength = round(importedInstancesSize / 4)

# Get the test sample from all the instances
testSampleList = random.sample(wineQualityMetricsInstanceList, testSampleLength)

# Copy the whole instance list
trainingSampleList = wineQualityMetricsInstanceList.copy()

# Get the training sample from the remaining instances
for removeInstance in testSampleList:
    trainingSampleList.remove(removeInstance)

# Get the wine quality values
wineQualityValues = numpy.ravel(
    HelperMethods.ClassListToClassPropertiesList(testSampleList, [WineQualityMetricsEnum.Quality.value]))

# For the every instance in the test sample
for testSample in testSampleList:
    #  Clear the wineQualityValues property of the instance
    testSample.WineQualityValues = None

# Transform the test class set to a list of list objects
testSampleList = HelperMethods.ClassListToClassPropertiesList(testSampleList,
                                                              [WineQualityMetricsEnum.FixedAcidity.value,
                                                               WineQualityMetricsEnum.VolatileAcidity.value,
                                                               WineQualityMetricsEnum.CitricAcid.value,
                                                               WineQualityMetricsEnum.ResidualSugar.value,
                                                               WineQualityMetricsEnum.Chlorides.value,
                                                               WineQualityMetricsEnum.FreeSulfurDioxide.value,
                                                               WineQualityMetricsEnum.TotalSulfurDioxide.value,
                                                               WineQualityMetricsEnum.Density.value,
                                                               WineQualityMetricsEnum.pH.value,
                                                               WineQualityMetricsEnum.Sulphates.value,
                                                               WineQualityMetricsEnum.Alcohol.value])

# Transform the training class set to a list of list object
trainingTargetSampleList = numpy.ravel(
    HelperMethods.ClassListToClassPropertiesList(trainingSampleList, [WineQualityMetricsEnum.Quality.value]))

# Transform the training class set to a list of list object
trainingSampleList = HelperMethods.ClassListToClassPropertiesList(trainingSampleList,
                                                                  [WineQualityMetricsEnum.FixedAcidity.value,
                                                                   WineQualityMetricsEnum.VolatileAcidity.value,
                                                                   WineQualityMetricsEnum.CitricAcid.value,
                                                                   WineQualityMetricsEnum.ResidualSugar.value,
                                                                   WineQualityMetricsEnum.Chlorides.value,
                                                                   WineQualityMetricsEnum.FreeSulfurDioxide.value,
                                                                   WineQualityMetricsEnum.TotalSulfurDioxide.value,
                                                                   WineQualityMetricsEnum.Density.value,
                                                                   WineQualityMetricsEnum.pH.value,
                                                                   WineQualityMetricsEnum.Sulphates.value,
                                                                   WineQualityMetricsEnum.Alcohol.value])

# Initialize the support vector classifier
supportVectorClassifier = SVC(kernel='linear')

# Fit the supportVectorClassifier using the training sample lists
supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

# Predict the target property values of the test sample set
wineQualityPrediction = supportVectorClassifier.predict(testSampleList)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

# https://stackoverflow.com/questions/21393704/scikit-learn-svm-giving-me-zero-error-but-cant-predict
# https://towardsdatascience.com/fine-tuning-a-classifier-in-scikit-learn-66e048c21e65
resultList = []
for index in range(len(wineQualityValues)):
    resultList.append(int(wineQualityPrediction[index]) - int(wineQualityValues[index]))

zeroCounter = 0
oneCounter = 0
for result in resultList:
    if result == 0:
        zeroCounter += 1
    if abs(result) == 1:
        oneCounter += 1

print("\nScores for the unedited data\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)
print("Zero counter: ", zeroCounter, "One counter: ", oneCounter)

# C_range = 10.0 ** numpy.arange(-2, 9)
# gamma_range = 10.0 ** numpy.arange(-5, 4)
# param_grid = dict(gamma=gamma_range, C=C_range)
# cv = StratifiedKFold()
#
# grid = GridSearchCV(SVC(), param_grid=param_grid, cv=cv)
# grid.fit(trainingSampleList, trainingTargetSampleList)
#
# print("The best classifier is: ", grid.best_estimator_)

##########################################################################

# Copy the test sample list
editedTestSampleList = testSampleList.copy()

# Part 1

# For every training sample...
for index in range(len(trainingSampleList)):

    # Remove the ph values
    trainingSampleList[index].pop(WineQualityMetricsEnum.pH.value)

# For every test sample...
for index in range(len(testSampleList)):

    # Remove the ph values
    testSampleList[index].pop(WineQualityMetricsEnum.pH.value)

# Fit the supportVectorClassifier using the training sample lists
supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

# Predict the target property values of the test sample set
wineQualityPrediction = supportVectorClassifier.predict(testSampleList)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the delete ph column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# Part 2

# Get the length of the first one third slice of the list
testSampleListOneThirdLength = round(len(editedTestSampleList) / 3)

# Get the length of the two third slices of the list
testSampleListTwoThirdLength = len(editedTestSampleList) - testSampleListOneThirdLength

Average = 0
for sampleList in editedTestSampleList[testSampleListOneThirdLength + 1:]:
    Average += sampleList[WineQualityMetricsEnum.pH.value]

Average /= testSampleListTwoThirdLength

# For every edited test sample in the first one third of the list...
for index in range(testSampleListOneThirdLength):

    # Remove the pH value
    editedTestSampleList[index][WineQualityMetricsEnum.pH.value] = Average

# Fit the supportVectorClassifier using the training sample lists
supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

# Predict the target property values of the test sample set
wineQualityPrediction = supportVectorClassifier.predict(testSampleList)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the average ph column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# Part 3

# For every edited test sample in the first one third of the list...
for index in range(testSampleListOneThirdLength):

    # Remove the pH value
    editedTestSampleList[index][WineQualityMetricsEnum.pH.value] = None

# Transform the test class set to a list of list objects
testSampleList = HelperMethods.ClassListToClassPropertiesList(testSampleList,
                                                              [WineQualityMetricsEnum.FixedAcidity.value,
                                                               WineQualityMetricsEnum.VolatileAcidity.value,
                                                               WineQualityMetricsEnum.CitricAcid.value,
                                                               WineQualityMetricsEnum.ResidualSugar.value,
                                                               WineQualityMetricsEnum.Chlorides.value,
                                                               WineQualityMetricsEnum.FreeSulfurDioxide.value,
                                                               WineQualityMetricsEnum.TotalSulfurDioxide.value,
                                                               WineQualityMetricsEnum.Density.value,
                                                               WineQualityMetricsEnum.Sulphates.value,
                                                               WineQualityMetricsEnum.Alcohol.value])

# Transform the training class set to a list of list object
trainingTargetSampleList = numpy.ravel(
    HelperMethods.ClassListToClassPropertiesList(trainingSampleList, [WineQualityMetricsEnum.pH.value]))

# Transform the training class set to a list of list object
trainingSampleList = HelperMethods.ClassListToClassPropertiesList(trainingSampleList,
                                                                  [WineQualityMetricsEnum.FixedAcidity.value,
                                                                   WineQualityMetricsEnum.VolatileAcidity.value,
                                                                   WineQualityMetricsEnum.CitricAcid.value,
                                                                   WineQualityMetricsEnum.ResidualSugar.value,
                                                                   WineQualityMetricsEnum.Chlorides.value,
                                                                   WineQualityMetricsEnum.FreeSulfurDioxide.value,
                                                                   WineQualityMetricsEnum.TotalSulfurDioxide.value,
                                                                   WineQualityMetricsEnum.Density.value,
                                                                   WineQualityMetricsEnum.Sulphates.value,
                                                                   WineQualityMetricsEnum.Alcohol.value])

# Initialise a logistic regression object
logisticRegression = LogisticRegression()

# Fit the logisticRegression using the training sample lists
logisticRegression.fit(trainingSampleList, trainingTargetSampleList)

# Predict the target property values of the test sample set
winePHPrediction = supportVectorClassifier.predict(testSampleList)

# Fit the supportVectorClassifier using the training sample lists
supportVectorClassifier.fit(trainingSampleList, trainingTargetSampleList)

# Predict the target property values of the test sample set
wineQualityPrediction = supportVectorClassifier.predict(testSampleList)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the Logistic Regression ph column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)
