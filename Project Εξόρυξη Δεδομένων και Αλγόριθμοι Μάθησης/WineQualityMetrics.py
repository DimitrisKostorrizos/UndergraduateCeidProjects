# TODO
class WineQualityMetrics:
    # Wine fixed acidity property
    FixedAcidity = None

    # Wine volatile acidity property
    VolatileAcidity = None

    # Wine citric acid concentration property
    CitricAcid = None

    # Wine residual sugar property
    ResidualSugar = None

    # Wine chlorides concentration property
    Chlorides = None

    # Wine free sulfur dioxide concentration property
    FreeSulfurDioxide = None

    # Wine total sulfur dioxide concentration property
    TotalSulfurDioxide = None

    # Wine density property
    Density = None

    # Wine pH property
    pH = None

    # Wine sulphates concentration property
    Sulphates = None

    # Wine alcohol concentration property
    Alcohol = None

    # Wine quality property
    Quality = None

    def __init__(self, fixedAcidity, volatileAcidity, citricAcid, residualSugar):
        self.FixedAcidity = fixedAcidity
        self.VolatileAcidity = volatileAcidity
        self.CitricAcid = citricAcid
        self.ResidualSugar = residualSugar
