function [Xq, Centers ,D] = LloydMax(x, N, min_value, max_value)

    % Calculate the encoding length
    EncodingLength = 2 ^ N;
    
    % Get the number of signal samples
    SignalSamples = length(x);
    
    % Calculate the step
    Step = (min_value - max_value)/EncodingLength;
    
    % Find the middle point
    MiddlePoint = mean(x);
    
    % Declare a vector that will contain the centers
    Centers = zeros(1, EncodingLength);
    
    % For every two adjacent samples...
    for index = 1: EncodingLength /2
        % Calculate the next center
        Centers(EncodingLength/2 + 1 - index) = MiddlePoint + index*Step;
        
        % Calculate the previous center
        Centers(EncodingLength/2 + index) = MiddlePoint - index*Step;
    end  
    
    % Declare a vector that will contain the distorsion
    D = [0,1];
    
    % Initialize the K to 2
    % K: The number of loops
    K = 2;
    
    % Declare a vector that will contain the encoded quantized signal
    Xq = zeros(1, SignalSamples);
    
    % While the difference between two successive loop is greater than
    % epsilon...
    while (abs(D(K) - D(K-1)) > eps)
        % Intialise the sum of the samples to 0
        SampleSum = 0;
        
        % Declare a vector that will contain the quantized samples
        QuantizedSamples = zeros(1, length(Centers));
        
        % Declare a vector that will contain the conditional mean for each
        % sample
        ConditionalMean = zeros(1, length(Centers));

        % Declare a vector that will contain the new quantization zones
        QuantizationZones = zeros(1, EncodingLength);
        
        % For every center, excluding the last...
        for index = 1:(length(Centers)-1)
            % Calculate the middle point between two centers
            QuantizationZones(index) = (Centers(index) + Centers(index+1))/2;
        end

        % For every sample...
        for index = 1:SignalSamples
            % For every zone, excluding the last...
            for counter = 1:(length(QuantizationZones)-1)
                % If the sample can be quantized in the selected zone...
                if QuantizationZones(counter) < x(index) && x(index) <= QuantizationZones(counter+1)
                    % Quantize that sample
                    Xq(index) = QuantizationZones(counter);
                    
                    % Add the mean distance from the quantization zone's
                    % center
                    SampleSum = SampleSum + abs(Centers(counter+1) - x(index));
                    
                    % Add the sample to the condional mean
                    ConditionalMean(counter) = ConditionalMean(counter) + x(index);
                    
                    % Count the quantized sample
                    QuantizedSamples(counter)   = QuantizedSamples(counter) + 1;
                end
            end
            
            % If the sample is on the minimum value...
            if x(index) == QuantizationZones(1)
                % Quantize that sample
                Xq(index) = QuantizationZones(1);
                
                % Add the mean distance from the quantization zone's
                % center
                SampleSum = SampleSum + abs(Centers(2) - x(index));
                
                % Add the sample to the condional mean
                ConditionalMean(1) = ConditionalMean(1) + x(index);
                
                % Count the quantized sample
                QuantizedSamples(1)   = QuantizedSamples(1) + 1;
            end
        end
		
		%Calculate the average distortion
        AverageDistortion = SampleSum/SignalSamples;
        
        % Increase the K
        K = K + 1;
        
        % Add the new average distorsion
        D(K) = AverageDistortion;

        % For every center, excluding the first and last center...
        for counter = 2:(length(Centers)-1)
            % If at least a sample was quantized into this quantization
            % zone...
            if QuantizedSamples(counter-1) ~= 0
                % Calculate the new center
                Centers(counter) = ConditionalMean(counter-1)/QuantizedSamples(counter-1);
            end
        end
    end
    
    % Transpose the quantized signal
    Xq = Xq';
end