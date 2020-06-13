import numpy
import random
from SVM import SVMHelperMethods
from sklearn.metrics import f1_score, precision_score
from sklearn.metrics import recall_score
from sklearn.svm import SVC
from SVM.WineQualityMetrics import WineQualityMetricsEnum

# Initialise the list that contains the rows that will be ignored during the import
ignoredRowsList = [0]

# Import the wine quality metrics from the csv file
wineQualityMetricsInstanceList = SVMHelperMethods.CsvImporter(
    "Project Εξόρυξη Δεδομένων και Αλγόριθμοι Μάθησης/SVM/winequality-red.csv", ",", ignoredRowsList)

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
    SVMHelperMethods.ClassListToClassPropertiesList(testSampleList, [WineQualityMetricsEnum.Quality.value]))

# For the every instance in the test sample
for testSample in testSampleList:
    #  Clear the wineQualityValues property of the instance
    testSample.WineQualityValues = None

# Transform the test class set to a list of list objects
testSampleList = SVMHelperMethods.ClassListToClassPropertiesList(testSampleList,
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
    SVMHelperMethods.ClassListToClassPropertiesList(trainingSampleList, [WineQualityMetricsEnum.Quality.value]))

# Transform the training class set to a list of list object
trainingSampleList = SVMHelperMethods.ClassListToClassPropertiesList(trainingSampleList,
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

print("\nScores for the unedited data\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# Get the length of the first one third slice of the list
editedTrainingSampleListLength = round(len(trainingSampleList) / 3)

# region Removed Column

wineQualityPrediction = SVMHelperMethods.RemovePHColumn(trainingSampleList, trainingTargetSampleList, testSampleList,
                                                        supportVectorClassifier)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the delete pH column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# endregion

# region Average pH Column

wineQualityPrediction = SVMHelperMethods.AveragePHColumn(trainingSampleList, trainingTargetSampleList, testSampleList,
                                                         supportVectorClassifier, editedTrainingSampleListLength)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the average pH column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# endregion

# region Logistic Regression pH Column

wineQualityPrediction = SVMHelperMethods.LogisticRegressionPHColumn(trainingSampleList, trainingTargetSampleList,
                                                                    testSampleList, supportVectorClassifier,
                                                                    editedTrainingSampleListLength)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the Logistic Regression pH column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# endregion

# region K-Means pH Column

wineQualityPrediction = SVMHelperMethods.KMeansPHColumn(trainingSampleList, trainingTargetSampleList, testSampleList,
                                                        supportVectorClassifier, editedTrainingSampleListLength)

# Calculate f1 score
wineQualityPredictionF1Score = f1_score(wineQualityPrediction, wineQualityValues, average=None)

# Calculate recall score
wineQualityPredictionRecall = recall_score(wineQualityPrediction, wineQualityValues, average=None, zero_division=1)

# Calculate precision score
wineQualityPredictionPrecision = precision_score(wineQualityPrediction, wineQualityValues, average=None)

print("\nScores for the K-Means pH column\n")
print("F1 Score: ", wineQualityPredictionF1Score)
print("Recall: ", wineQualityPredictionRecall)
print("Precision: ", wineQualityPredictionPrecision)

# endregion
