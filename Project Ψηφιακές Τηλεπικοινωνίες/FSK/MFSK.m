function [OutputBitMatrix, OutputSymbolVector, InputSymbolVector, InputBitMatrix] = MFSK(N, M, SNR)
    
    % Get the bits per symbol
    BitPerSymbol = ceil(log2(M));
    
    % Get the number of symbols
    NumberOfSymbols = ceil(N/BitPerSymbol);
    
    % Generate a matrix that contains the bit per symbol
    % Row: Symbol
    % Columns: Bits that represent the symbol
    BitMatrix = randsrc(NumberOfSymbols, BitPerSymbol,[0 1]);
    
    % Return the BitMatrix
    InputBitMatrix = BitMatrix;
    
    % Encode the binary matrix to decimal symbols
    SymbolVector = bi2de(BitMatrix);
    
    % Set the input symbol vector
    InputSymbolVector = SymbolVector;
    
    % Calculate the symbol period
    TSymbol = 4 * 10^(-6);
    
    % Calculate the sampling period
    Ts = 0.1 * 10^(-6);
    
    % Calculate the number of samples
    NumberOfSamples = TSymbol/Ts;
    
    % Calculate the frequency
    Fc = 2.5 * 10 ^ 6;
    
    % Calaculate the pulse amplitude
    Gt = sqrt(2/TSymbol);
    
    % Calculate the pulse energy 
    PulseEnergy = TSymbol * Gt^2;
    
    % Initialise a temp variable to 0
    % Temp: The sum of the energy of the symbols
    temp = 0;
    
    % For every energy level...
    for index = 1 : M
        % Add the energy required
        temp = temp + (2 * index - 1 - M) ^ 2;
    end
    
    % Calculate the average pulse amplitude
    A = sqrt(M / (PulseEnergy * temp));
    
    % Declare a vector that will contain the amplitude per symbol
    SymbolAmplitude = zeros(M,1); 
    
    % For every symbol...
    for index = 1 : M
        % Calculate the amplitude per symbol
        SymbolAmplitude(index) = (2 * index - 1 - M) * A;
    end
    
    % Initialise a counter to 1
    % counter: The couter points to the position of the modulated signal
    counter = 1;
    
    % Delcare a vector for the modulated signal
    Sm = zeros(NumberOfSymbols * NumberOfSamples, 1);
    
    % For every symbol...
    for index = 1 : NumberOfSymbols        
            
        symbol = SymbolVector(index);
        
        % For every sample...
        for Time = 0 : Ts : TSymbol - Ts
            
            % Calculate the modulated signal
            Sm(counter) = SymbolAmplitude(SymbolVector(index) + 1) * Gt * cos(2 * pi * (Fc + symbol/TSymbol) * Time);
            
            % Increase the counter
            counter = counter + 1;
        end
    end
    
    % Calculate the variance
    Variance = 10 ^ -(SNR/10) / BitPerSymbol;
    
    % Calculate the additive white Gausian noise
    AWGNoise = sqrt(Variance) * randn(NumberOfSymbols * 40, 1);
    
    % Add the additive white Gausian noise to the signal
    Rn = Sm + AWGNoise;
    
    % Initialise a counter to 1
    % counter: The couter points to the position of the demodulated symbol
    counter = 1;
    
    % Declare a vector for the demodulated symbols
    Smt = zeros(NumberOfSymbols, 1);
    
    % For every symbol...
    for index = 1 : NumberOfSymbols
            
        symbol = SymbolVector(index);
        
        % For every sample...
        for Time = 0 : Ts : TSymbol - Ts
            
            % Calculate the demodulated symbol
            Smt(index) = Smt(index) + Rn(counter) * Gt * cos(2 * pi * (Fc + symbol/TSymbol) * Time) * Ts;
            
            % Increase the counter
            counter = counter + 1;
        end
    end

    % Declare a vector for the symbol distance
    DistanceVector = zeros(1, M);
    
    % Declare a vector for the demapped symbols
    SymbolVector = zeros(NumberOfSymbols, 1);
    
    % For every symbol...
    for counter = 1 : NumberOfSymbols
        
        % For every symbol type...
        for index = 1 : M
            
            % Calculate the absolute distance between the initial symbol
            % and the demapped symbol
            DistanceVector(index) = abs(Smt(counter) - SymbolAmplitude(index));
        end
        
        % Get the index that points to the minimum diastance
        [~,MinimumPosition] = min(DistanceVector);
        
        % Get the most similar symbol
        SymbolVector(counter) = MinimumPosition - 1;
    end
    
    % Set the output symbol vector
    OutputSymbolVector = SymbolVector;
    	
    % Decode the decimal symbols to bits
    OutputBitMatrix = de2bi(SymbolVector, BitPerSymbol);
end