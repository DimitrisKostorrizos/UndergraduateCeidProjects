function [OutputBitMatrix, OutputSymbolVector, InputSymbolVector, InputBitMatrix] = PSK(N,M,ChannelType,SNR)   
    %Filter
    RollOffFactor = 0.3;
    HyperSamplingFactor = 4;
    HyperSamplingPeriods = 6;
    Filter = rcosdesign(RollOffFactor,HyperSamplingPeriods,HyperSamplingFactor); % Hyper sampled filter
    
    %Bit Sequence Creation
    SymbolLength = log2(M);
    NumberOfSymbols = ceil(N/SymbolLength);
    BitSequence = randi([0 1],1,NumberOfSymbols * SymbolLength);
    BitMatrix = zeros(NumberOfSymbols, SymbolLength); % Symbol Matrix, every row has bit representation of the symbol
    
    VectorIndex = 1;
    for index = 1:NumberOfSymbols % Convert the Bit Sequence to Bit Matrix
        for counter = 1:SymbolLength
            BitMatrix(index, counter) = BitSequence(VectorIndex);
            VectorIndex = VectorIndex + 1;
        end
    end
    InputBitMatrix = BitMatrix; % Every row has the bit representation of each symbol
    
    SymbolVector = bi2de(BitMatrix,"left-msb"); % Encode the Bit Matrix to Decimal Symbol Vector
    InputSymbolVector = SymbolVector';
    
    HyperSampledSymbolVector = upsample(SymbolVector,HyperSamplingFactor); % Hyper Sampled Symbol Vector
    
    PhaseVector = zeros(1, M); % Symbol Phase Vector
    AmplitudeVector = zeros(1, M); % Symbol Amplitude Vector
    for index = 1:length(AmplitudeVector)
        PhaseVector(index) = (2 * pi * (index - 1)) / M;
        AmplitudeVector(index) = complex(cos(PhaseVector(index)), sin(PhaseVector(index))); % Generate the complex symbol
    end
    
    ModulatedSymbols = zeros(1,length(HyperSampledSymbolVector));
    for index = 1: length(HyperSampledSymbolVector)
        ModulatedSymbols(index) = AmplitudeVector(HyperSampledSymbolVector(index) + 1);
    end
    
    
    
    FilteredModulatedSymbols = filter(Filter,1,ModulatedSymbols); % Apply Sender Filter
	
    %Channel
	if(ChannelType == "non-ideal")    
		h = [0.04, -0.05, 0.07, -0.21, -0.5, 0.72, 0.36, 0, 0.210, 0.03, 0.07];
		HyperSampledh = upsample(h,HyperSamplingFactor);  % Hyper sample the Channel's Impulse
		FilteredModulatedSymbols = filter(HyperSampledh,1,FilteredModulatedSymbols); % Apply Channel's Impulse   
	else
		if (ChannelType ~= "ideal")
			error("Channel Type has to be either ideal or non-ideal");
		end
	end
    
	
    %AWGN
    SignalPower = sum(abs(FilteredModulatedSymbols).^2)/length(FilteredModulatedSymbols); % Signal power
    Variance = SignalPower/(10 ^ (SNR/10)); % Noise variance
    AWGNoise = sqrt(Variance) * (randn(size(FilteredModulatedSymbols)) + 1j*randn(size(FilteredModulatedSymbols))); % Real and Imaginary Noise Generation
    FilteredModulatedSymbols = FilteredModulatedSymbols + AWGNoise; % Add the complex noise to the modulated symbols
    
    FilteredModulatedSymbols = filter(Filter,1,FilteredModulatedSymbols);% Apply Receiver Filter
    
    FilteredModulatedSymbols = downsample(FilteredModulatedSymbols, HyperSamplingFactor); % Downsample the received symbols
    
    % Euclidean Distance
    ReceivedSymbolVector = zeros(1,length(FilteredModulatedSymbols));
    EuclideanDistance = zeros(1,M);
    for counter = 1:length(FilteredModulatedSymbols)
        for index = 1:M
            SymbolDistanceVector = [real(FilteredModulatedSymbols(counter)) - real(AmplitudeVector(index)), imag(FilteredModulatedSymbols(counter)) - imag(AmplitudeVector(index))];
            EuclideanDistance(index) = norm(SymbolDistanceVector); % Euclidean norm for each symbol
        end
        [~,MinimumPosition] = min(EuclideanDistance); % Find which symbol has the minimum distance from the received symbol
        ReceivedSymbolVector(counter) = MinimumPosition - 1; % Most Similar Symbol
    end
    
    OutputSymbolVector = ReceivedSymbolVector;
    OutputBitMatrix = de2bi(ReceivedSymbolVector', "left-msb"); % Decode the received symbols to bit
 end