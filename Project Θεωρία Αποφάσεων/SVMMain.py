import SVMHelperMethods
import pandas
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.svm import SVC

# Import the wine quality train sample from the excel file
trainingSample = pandas.DataFrame(pandas.read_excel("Wine_Training.xlsx", header = 0))

# Import the wine quality test sample from the excel file
testSample = pandas.DataFrame(pandas.read_excel("Wine_Testing.xlsx", header = 0))

# Transform the training class set to a list of list object
qualityTrainingSample = trainingSample["quality"]

# Transform the training class set to a list of list object
trainingSampleList = trainingSample[["fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides", "free sulfur dioxide", "total sulfur dioxide", "density", "pH", "sulphates", "alcohol"]]

# Initialize the support vector classifier
supportVectorClassifier = SVC(kernel='linear')

# Fit the supportVectorClassifier using the training sample lists
supportVectorClassifier.fit(trainingSampleList, qualityTrainingSample)

# Predict the target property values of the test sample set
wineQualityPrediction = supportVectorClassifier.predict(testSample)

# Plot the values
plt.plot(range(0, 401), wineQualityPrediction)

# Set the x label
plt.xlabel("Elements")

# Set the y label
plt.ylabel("Prediction")

# Save the plot
plt.savefig("SVC.png")

# Clear the plot
plt.clf()

# Get the length of the first one third slice of the list
editedTrainingSampleLength = round(len(trainingSampleList) / 3)

# Predict the wine quality, without using the pH column
wineQualityPrediction = SVMHelperMethods.RemovePHColumn(trainingSampleList, qualityTrainingSample, testSample, supportVectorClassifier)

# Plot the values
plt.plot(range(0, 401), wineQualityPrediction)

# Set the x label
plt.xlabel("Elements")

# Set the y label
plt.ylabel("Prediction")

# Save the plot
plt.savefig("RemovePHSVC.png")

# Clear the plot
plt.clf()

# Predict the wine quality, by using the average pH for the pH column
wineQualityPrediction = SVMHelperMethods.AveragePHColumn(trainingSampleList, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength)

# Plot the values
plt.plot(range(0, 401), wineQualityPrediction)

# Set the x label
plt.xlabel("Elements")

# Set the y label
plt.ylabel("Prediction")

# Save the plot
plt.savefig("AveragePHSVC.png")

# Clear the plot
plt.clf()

# Predict the wine quality, by using Logistic Regression to predict the pH column
wineQualityPrediction = SVMHelperMethods.LogisticRegressionPHColumn(trainingSampleList, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength)

# Plot the values
plt.plot(range(0, 401), wineQualityPrediction)

# Set the x label
plt.xlabel("Elements")

# Set the y label
plt.ylabel("Prediction")

# Save the plot
plt.savefig("LogisticRegressionSVC.png")

# Clear the plot
plt.clf()

# Predict the wine quality, by using KMeans clustering to predict the pH column
wineQualityPrediction = SVMHelperMethods.KMeansPHColumn(trainingSampleList, qualityTrainingSample, testSample, supportVectorClassifier, editedTrainingSampleLength)

# Plot the values
plt.plot(range(0, 401), wineQualityPrediction)

# Set the x label
plt.xlabel("Elements")

# Set the y label
plt.ylabel("Prediction")

# Save the plot
plt.savefig("KmeansPHPredictionSVC.png")

# Clear the plot
plt.clf()