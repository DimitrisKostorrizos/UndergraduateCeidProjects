import csv
import logging

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
        with open(fileName, encoding='utf-8') as csvFile:

            # Create a csv file reader to read the opened file
            csvFileReader = csv.reader(csvFile, delimiter=delimiter)

            # Initialize an index for the csv file lines
            csvLineIndex = 0

            # Initialize a list that will contain the csv rows
            rowList = []

            # For each row in the csv file...
            for csvFileRow in csvFileReader:

                # If the row has to be imported...
                if csvLineIndex not in ignoredRows:
                    
                    # Add the row to the list
                    rowList.append(csvFileRow)

                # Increase the csv line index
                csvLineIndex += 1

            # Return the imported csv rows
            return rowList

    # Catch the IOError
    except IOError:

        # Inform the user
        logging.exception("Csv file cannot be opened.")