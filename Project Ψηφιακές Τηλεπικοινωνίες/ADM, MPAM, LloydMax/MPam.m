function [OutputBitMatrix,InputBitMatrix] = MPam(N,M,EncodingType,SNR)
    
    BitPerSymbol = ceil(log2(M)); %Bits per Symbol
    
    NumberOfSymbols = ceil(N/BitPerSymbol); %NumberOfSymbols

    BitMatrix = randi([0 1],NumberOfSymbols,BitPerSymbol); %Bit Matrix
    InputBitMatrix = BitMatrix;
    
    DecimalVector = bi2de(BitMatrix); %Bit Matrix to Decimal Vector
    
    if EncodingType == "Gray"       
        SymbolVector = bin2gray(DecimalVector, 'pam', M); %Gray Encoded Decimal Vector
    else
        SymbolVector = DecimalVector; %Simple Encoded Decimal Vector
    end
    
    TSymbol = 4*10^(-6); %Symbol Period(sec)
    
    Ts = 0.1 * 10^(-6); %Sampling Period(sec)
    
    NumberOfSamples = TSymbol/Ts; %NumberOfSamples
    Fc = 2.5*10^6; %Frequency
    Gt = sqrt(2/TSymbol); %Pulse Amplitude
    PulseEnergy = TSymbol * Gt^2; %PulseEnergy
    
    temp = 0;
    for index = 1 : M
        temp = temp + (2 * index - 1 - M) ^ 2;
    end
    A = sqrt(M / (PulseEnergy * temp)); %Average Amplitude
    
    SymbolAmplitude = zeros(M,1); 
    for index = 1 : M
        SymbolAmplitude(index) = (2*index - 1 - M) * A; %Amplitude per Symbol
    end
    
    counter = 1; %Modulator
    Sm = zeros(NumberOfSymbols * NumberOfSamples,1);
    for index = 1 : NumberOfSymbols 
        for Time = 0 : Ts : TSymbol - Ts
            Sm(counter) = SymbolAmplitude(SymbolVector(index) + 1) * Gt * cos(2 * pi * Fc * Time);
            counter = counter + 1;
        end
    end

	SNR = 10 ^ (SNR/10);
    Variance = 1/(SNR/10) ^ 10 * (2*log2(M)); %AWGN
    AWGNoise = Variance * randn(size(Sm)); %Noise Generator
    Rn = Sm + AWGNoise;

    counter = 1;
    Smt = zeros(NumberOfSymbols,1); %Demodulator
    for index = 1 : NumberOfSymbols
        for Time = 0 : Ts : TSymbol - Ts
            Smt(index) = Smt(index) + Rn(counter) * Gt * cos(2 * pi * Fc * Time) * Ts;
            counter = counter + 1;
        end
    end


    DistanceVector = zeros(1,M); %Demapper
    SymbolVector = zeros(NumberOfSymbols,1);
    for counter = 1 : NumberOfSymbols 
        for index = 1 : M
            DistanceVector(index) = abs(Smt(counter) - SymbolAmplitude(index)); %Distance Vector
        end
        [~,MinimumPosition] = min(DistanceVector);
        SymbolVector(counter) = MinimumPosition - 1; %Most Similar Symbol
    end

    if EncodingType == "Gray"       
        DecimalVector = gray2bin(SymbolVector, 'pam', M); %Gray Vector to Decimal Vector
    else
        DecimalVector = SymbolVector; %Simple Encoded Decimal Vector
    end
	
    OutputBitMatrix = de2bi(DecimalVector); %Decimal Vector to Bit Vector
end