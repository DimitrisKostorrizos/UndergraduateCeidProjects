import random
import HelperMethods
from sklearn.metrics import f1_score
from sklearn.svm import SVC
import numpy

# Initialise the list that contains the rows that will be ignored during the import
ignoredRowsList = [0]

# Initialise the list that contains the columns that will be ignored during the import
ignoredColumnsList = []

# Import the wine quality metrics from the csv file
wineQualityMetricsInstanceList = HelperMethods.CsvImporter("Project Εξόρυξη Δεδομένων και Αλγόριθμοι Μάθησης/winequality-red.csv", ",", ignoredRowsList, ignoredColumnsList)

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

# Calculate the size of the training sample
trainingSampleLength = len(trainingSampleList)

# Get the quality column
quality = numpy.ravel(HelperMethods.ClassListToClassPropertiesList(testSampleList, [11]))

# For the every instance in the test sample
for testSample in testSampleList:
    #  Clear the quality property of the instance
    testSample.Quality = None

# Initialize the support vector classifier
classifier = SVC(kernel = 'linear')

# Transform the training class set to a list of list object
trainingSamplePropertiesList = HelperMethods.ClassListToClassPropertiesList(trainingSampleList, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])

# Transform the training class set to a list of list object
trainingTargetSamplePropertiesList = numpy.ravel(HelperMethods.ClassListToClassPropertiesList(trainingSampleList, [11]))

# Fit the classifier using the training sample lists
classifier.fit(trainingSamplePropertiesList, trainingTargetSamplePropertiesList)

# Transform the test class set to a list of list objects
testTargetSamplePropertiesList = HelperMethods.ClassListToClassPropertiesList(testSampleList, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])

# Predict the target property values of the test sample set
prediction = classifier.predict(testTargetSamplePropertiesList)

# Calculate F1 score
test = f1_score(prediction, quality, average =None)

print(test)