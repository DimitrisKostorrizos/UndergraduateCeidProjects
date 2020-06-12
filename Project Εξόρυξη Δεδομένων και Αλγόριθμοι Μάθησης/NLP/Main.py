import random

import nltk
import numpy
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

    #
    tokenList = []

    # For every token in the list
    for token in titleToken:

        # If the token isn't a stop word...
        if token not in stopWordsList:

            # Add the token to the token sentence list
            tokenList.append(token)

    # Add the token to the token sentence list
    filteredTokenList.append(' '.join(tokenList))

# Initialise a Tf-Idf vectorizer object
tfidfVectorizer = TfidfVectorizer(use_idf=True, stop_words=stopWordsList)

# Fit and transform the transformer using the filtered word matrix
tfidfFilteredTokenMatrix = tfidfVectorizer.fit_transform(filteredTokenList)

# Declare a list that contain the sample tuples
tfidfTitleRepresentationFlagSamplesList = []

# Initialise an index to 0
index = 0

# For every tfidf title representation...
for tfidfTitleRepresentation in tfidfFilteredTokenMatrix:

    # Link the tfidf title representation and the flag
    tfidfTitleRepresentationFlagTuple = (tfidfTitleRepresentation, flagsList[index])

    # Add the tuple to the list
    tfidfTitleRepresentationFlagSamplesList.append(tfidfTitleRepresentationFlagTuple)

    # Increase the index
    index += 1

# Calculate the size of the test sample
testSampleLength = round(len(tfidfTitleRepresentationFlagSamplesList) / 4)

#
multiLayerPerceptronClassifier = MLPClassifier()

#
multiLayerPerceptronClassifier.fit(tfidfFilteredTokenMatrix[:10], flagsList[:10])
print("Last")
