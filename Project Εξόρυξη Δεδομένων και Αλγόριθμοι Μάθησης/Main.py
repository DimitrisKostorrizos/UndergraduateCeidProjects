import random
import HelperMethods
import sklearn

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

# Calculate the size of the test sample
trainingSampleLength = importedInstancesSize - testSampleLength

# Get the test sample from all the instances
testSample = random.sample(wineQualityMetricsInstanceList, testSampleLength)
