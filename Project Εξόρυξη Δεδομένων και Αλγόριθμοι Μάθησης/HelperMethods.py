import csv
import logging
import WineQualityMetrics

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
        
    ignoredColumns : list<int>
        A list containing the index of the csv file columns that will be ignored
"""
def CsvImporter(fileName, delimiter, ignoredRows, ignoredColumns):

    # Try to open the csv file
    try:
        with open(fileName) as csvFile:

            # Create a csv file reader to read the opened file
            csvFileReader = csv.reader(csvFile, delimiter = delimiter)

            # Initialize an index for the csv file lines
            csvLineIndex = 0

            # Initialize a list that will contain the class instances
            instanceList = []

            # For each row in the csv file...
            for csvFileRow in csvFileReader:

                # If the row has to be imported...
                if csvLineIndex not in ignoredRows:

                    # For every deselected column
                    for csvFileColumn in ignoredColumns:

                        # Set the property associated to the ignored column to None
                        csvFileRow[csvFileColumn] = None

                    # Create the class instance based on the imported row
                    classInstance = WineQualityMetrics.WineQualityMetrics(csvFileRow[0], csvFileRow[1], csvFileRow[2], csvFileRow[3], csvFileRow[4], csvFileRow[5], csvFileRow[6], csvFileRow[7],  csvFileRow[8], csvFileRow[9], csvFileRow[10], csvFileRow[11])

                    # Add the class instance to the list
                    instanceList.append(classInstance)

                # Increase the csv line index
                csvLineIndex = csvLineIndex + 1

            # Return the imported class instances
            return instanceList

    # Catch the IOError
    except IOError:

        # Inform the user
        logging.exception("Csv file cannot be opened.")
