import csv


def CsvImporter(fileName, delimiter, importingClass):
    # Try to open the csv file
    with open(fileName) as csvFile:
        # Create a csv file reader to read the opened file
        csvFileReader = csv.reader(csvFile, delimiter=delimiter)

    # Return None if an error occurred
    return None
