function [OutOfRangeSamplePossibility, SQNR, AverageDistortion] = my_quantizerSQNRCalculation()
    
    % Intialize the M
    M = 10000;
    
    % Intialize the min_value
    min_value = 0;
    
    % Intialize the max_value
    max_value = 4;
    
    % Calculate the cyclic symmetric complex Gaussian sample, with mean distribution of value 0 and dispersion 1
    CSCGSamples = (randn(M,1) + 1i * randn(M,1))/sqrt(2);
    
    % Calculate the exponential distribution samples
    EDSamples = abs(CSCGSamples).^2;
    
    % Initialize an index for the N values
    NIndex = 1;
    
    % Declare a vector the will contain the average distortion
    AverageDistortion = zeros(1,2);
    
    % Declare a vector the will contain the SQNR
    SQNR = zeros(1,2);
    
    % For every N...
    for N = [4, 6]
        
        % Execute the my_quantizer function
        [xq, ~] = my_quantizer(EDSamples, N, min_value, max_value);
        
        % Calculate the SQNR
        SQNR(NIndex) = 10 * log10(sum(xq.^2) / sum((xq - EDSamples).^2));
        
        % Calculate the average distortion
        AverageDistortion(NIndex) = sum(abs(xq - EDSamples))/ length(xq);
        
        % Increase the N index
        NIndex = NIndex + 1;
    end
    
    % Intialize a counter for the, out of range samples, to 0
    OutOfRangeSampleCounter = 0;
    
    % For every sample...
    for index = 1 : length(EDSamples)
        
        % If the sample is out of the dynamic range...
        if(EDSamples(index) > max_value || EDSamples(index) < min_value)
            % Increase the counter
            OutOfRangeSampleCounter = OutOfRangeSampleCounter + 1;
        end
    end
    
    % Calculate the out of range sample possibility
    OutOfRangeSamplePossibility = OutOfRangeSampleCounter / length(CSCGSamples);
end