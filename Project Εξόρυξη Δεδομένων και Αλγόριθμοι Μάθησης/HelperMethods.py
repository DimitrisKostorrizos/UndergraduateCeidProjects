import csv

"""
Returns a list that contain the imported, from a csv file rows, as class instances

Attributes
    ----------
    fileName : str
        A string that contains the file path and the file name
        
    delimiter : str
        The delimiter used in the csv
        
    importingClass : class
        The class object that the imported instances will be based on
        
    ignoredRows : list<int>
        A list containing the index of the csv file rows that will be ignored
        
    ignoredColumns : list<int>
        A list containing the index of the csv file columns that will be ignored
"""
def CsvImporter(fileName, delimiter, importingClass, ignoredRows, ignoredColumns):

    # Try to open the csv file
    with open(fileName) as csvFile:

        # Create a csv file reader to read the opened file
        csvFileReader = csv.reader(csvFile, delimiter = delimiter)

        # Initialize a index for the csv file lines
        csvLineIndex = 0

        # For each row in the csv file...
        for csvFileRow in csvFileReader:

            # If the row has to be imported...
            if csvLineIndex not in ignoredRows:
                print(csvFileRow)
            # Increase the csv line index
            csvLineIndex = csvLineIndex + 1
    # Return None if an error occurred
    return None
