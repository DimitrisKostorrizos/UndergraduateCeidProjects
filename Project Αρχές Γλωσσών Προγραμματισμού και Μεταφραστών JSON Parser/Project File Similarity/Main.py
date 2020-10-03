import string
from collections import Counter
from math import sqrt
from math import pow
from itertools import combinations
translate_tab = str.maketrans('', '', string.punctuation)#translate_tab to remove all puncuation from the word.
word_maps_list = []
filenames_list = []
similarities = {}#dictionary that will store the files and their similarity value.
top_doc = -1
num_of_doc = int(input("Enter the number of documents."))
while(num_of_doc < 2):#the number of files, must be at least 2.
        num_of_doc = int(input("To compare, you must enter at least 2 documents. Try again."))
comb = list(combinations(range(num_of_doc),2))#calculate the maximum combinations of (num_of_doc,2) elements.
for counter in range(num_of_doc):#for every file that wil be entered.
        print(f"Enter the filename of the document, number {counter+1}:")
        filenames_list.append(input())#store the filename, for printing later.
        current_file = open(filenames_list[-1], "r")#open the file that has the most recently entered filename.
        word_maps_list.append(Counter())#create and store a Counter(dictionary) for every file.
        for line in current_file:
                for word in line.split():#for every word split by white space and period
                        word_maps_list[-1].update([word.lower().translate(translate_tab)])#add the lowercase word without puncuation in the counter
        current_file.close()#close the file that has the most recently entered filename.
for left_value,right_value in comb:#unpacking the tuple
        dot_product = 0
        norm1 = 0
        norm2 = 0
        for i in (word_maps_list[left_value].keys() | word_maps_list[right_value].keys()):#check for every word in the union of the 2 texts words.
                dot_product += word_maps_list[left_value].get(i,0) * word_maps_list[right_value].get(i,0)#if the word doesn't exist in a document, the returned value is 0.
                norm1 += pow(word_maps_list[left_value].get(i,0),2)
                norm2 += pow(word_maps_list[right_value].get(i,0),2)
        norm1 = sqrt(norm1)
        norm2 = sqrt(norm2)
        similarity = (dot_product / (norm1 * norm2)) * 100
        similarities[left_value,right_value] = round(similarity,1)#the key of the dictionary is the tuple(text number,text number).
print("How many TOP-K most similar documents you want to print? Enter the K number, it has to be between",0,"and",len(comb),".")
top_doc = int(input())
while(top_doc < 0 or top_doc > len(comb)):#K must be between 0 and (num_of_doc,2).
        top_doc = int(input("The K number must be in the above range.Try again."))     
print("TOP -",top_doc,"most similar documents:")
for (left_value,right_value),i in sorted(similarities.items(), key=lambda x: x[1],reverse=True)[:top_doc]:#sort a dictionary based on value,descending.
    print("File: ",filenames_list[left_value],"    File: ",filenames_list[right_value]," Similarity = ",i,"%")

