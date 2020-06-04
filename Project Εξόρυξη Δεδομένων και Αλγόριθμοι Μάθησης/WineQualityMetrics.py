""" A class that represents the wine quality metrics"""
class WineQualityMetrics:

    """Default initialization method"""
    def __init__(self, fixedAcidity, volatileAcidity, citricAcid, residualSugar, chlorides, freeSulfurDioxide, totalSulfurDioxide, density, pH, sulphates, alcohol, quality):

        # Wine fixed acidity property
        self.FixedAcidity = float(fixedAcidity)

        # Wine volatile acidity property
        self.VolatileAcidity = float(volatileAcidity)

        # Wine citric acid concentration property
        self.CitricAcid = float(citricAcid)

        # Wine residual sugar property
        self.ResidualSugar = float(residualSugar)

        # Wine chlorides concentration property
        self.Chlorides = float(chlorides)

        # Wine free sulfur dioxide concentration property
        self.FreeSulfurDioxide = float(freeSulfurDioxide)

        # Wine total sulfur dioxide concentration property
        self.TotalSulfurDioxide = float(totalSulfurDioxide)

        # Wine density property
        self.Density = float(density)

        # Wine pH property
        self.pH = float(pH)

        # Wine sulphates concentration property
        self.Sulphates = float(sulphates)

        # Wine alcohol concentration property
        self.Alcohol = float(alcohol)

        # Wine quality property
        self.Quality = float(quality)

    def ClassToClassPropertiesList(self):
        return [self.FixedAcidity, self.VolatileAcidity, self.CitricAcid, self.ResidualSugar, self.Chlorides, self.FreeSulfurDioxide, self.TotalSulfurDioxide, self.Density, self.pH, self.Sulphates, self.Alcohol, self.Quality]
