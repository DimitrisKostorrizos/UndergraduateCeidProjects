""" A class that represents the wine quality metrics"""
class WineQualityMetrics:

    """Default initialization method"""
    def __init__(self, fixedAcidity, volatileAcidity, citricAcid, residualSugar, chlorides, freeSulfurDioxide, totalSulfurDioxide, density, pH, sulphates, alcohol, quality):

        # Wine fixed acidity property
        self.FixedAcidity = fixedAcidity

        # Wine volatile acidity property
        self.VolatileAcidity = volatileAcidity

        # Wine citric acid concentration property
        self.CitricAcid = citricAcid

        # Wine residual sugar property
        self.ResidualSugar = residualSugar

        # Wine chlorides concentration property
        self.Chlorides = chlorides

        # Wine free sulfur dioxide concentration property
        self.FreeSulfurDioxide = freeSulfurDioxide

        # Wine total sulfur dioxide concentration property
        self.TotalSulfurDioxide = totalSulfurDioxide

        # Wine density property
        self.Density = density

        # Wine pH property
        self.pH = pH

        # Wine sulphates concentration property
        self.Sulphates = sulphates

        # Wine alcohol concentration property
        self.Alcohol = alcohol

        # Wine quality property
        self.Quality = quality

    def ClassToClassPropertiesList(self):
        return [self.FixedAcidity, self.VolatileAcidity, self.CitricAcid, self.ResidualSugar, self.Chlorides, self.FreeSulfurDioxide, self.TotalSulfurDioxide, self.Density, self.pH, self.Sulphates, self.Alcohol, self.Quality]
