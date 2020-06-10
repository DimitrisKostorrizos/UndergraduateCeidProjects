import random

import nltk
from nltk.corpus import stopwords
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.neural_network import MLPClassifier

from NLP import HelperMethods


# Initialise the list that contains the rows that will be ignored during the import
ignoredRowsList = [0]

# Import the wine quality metrics from the csv file
titlesFlagList = HelperMethods.CsvImporter(
    "Project Εξόρυξη Δεδομένων και Αλγόριθμοι Μάθησης/NLP/onion-or-not.csv", ",", ignoredRowsList)

# Declare a list for the title
titlesList = []

# Declare a list for the scores
flagsList = []

# For every row in the title-scores list...
for row in titlesFlagList:

    # Add the title to the title list
    titlesList.append(row[0])

    # Add the flag to the title list
    flagsList.append(row[1])

# Declare a list for the title tokens
titleTokenList = []

# For every title in the titles list
for title in titlesList:

    # Append the title's token to the list
    titleTokenList.append(nltk.word_tokenize(title))

# Declare porter stemmer
ps = nltk.PorterStemmer()

# Declare list for the stemmed tokens list
stemTokensList = []

# For every token list...
for tokenList in titleTokenList:

    # Declare a list that will contain the sentence tokens
    sentenceTokenList = []

    # For every token...
    for token in tokenList:

        # Append the stemmed token
        sentenceTokenList.append(ps.stem(token))

    # Append the list to the stem tokens list
    stemTokensList.append(sentenceTokenList)

# Get the english stop words list
stopWordsList = set(stopwords.words('english'))

# Declare a list for filtered token list
filteredTokenList = []

# For the title token list...
for titleToken in titleTokenList:

    # For every token in the list
    for token in titleToken:

        # If the token isn't a stop word...
        if token not in stopWordsList:

            # Add the token to the token sentence list
            filteredTokenList.append(token)

# Initialise a Tf-Idf vectorizer object
tfidfVectorizer = TfidfVectorizer(use_idf=True, stop_words=stopWordsList)

# Fit and transform the transformer using the filtered word matrix
tfidfFilteredTokenMatrix = tfidfVectorizer.fit_transform(filteredTokenList)


f = tfidfVectorizer.get_feature_names()

titleSamplesList = []
#
for titleTokens in titleTokenList:

    tfidfTitleRepresentation = []

    for token in titleTokens:
        if token in filteredTokenList:

            tfidfTitleRepresentation.append(f[token])

        else:
            tfidfTitleRepresentation.append(0)

    titleSamplesList.append(tfidfTitleRepresentation)





# Calculate the size of the test sample
testSampleLength = round(len(titlesFlagList) / 4)

# Get the test sample from all the instances
testSampleList = random.sample(titlesFlagList, testSampleLength)

# Copy the whole instance list
trainingSampleList = titlesFlagList.copy()

# Get the training sample from the remaining instances
for removeInstance in testSampleList:
    trainingSampleList.remove(removeInstance)

# Declare a list for the scores
trainingTargetSampleList = []

# For every row in the title-scores list...
for row in titlesFlagList:

    # Add the title to the title list
    titlesList.append(row[0])

    # Add the flag to the title list
    flagsList.append(row[1])

#
multiLayerPerceptronClassifier = MLPClassifier()

#
multiLayerPerceptronClassifier.fit(trainingSampleList, te)
print()
