import csv

# Returns a list that contain the imported class instances TODO
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
