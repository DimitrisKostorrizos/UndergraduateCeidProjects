function [xq, centers] = my_quantizer(x, N, min_value, max_value)
    
% Get the number of signal samples
    SignalSamples = length(x);

    % If there is at least one sample that is less that min_value...
    if min(x) < min_value
        
        % For every sample...
        for index = 1 : SignalSamples
            
            % If the sample is less than the min value...
            if x(index) < min_value
                % Set the sample to the min_value
                x(index) = min_value;
            end
        end
    end
    
    % If there is at least one sample that is greater that max_value...
    if max(x) > max_value
        
        % For every sample...
        for index = 1 : SignalSamples
            
            % If the sample is greater than the max value...
            if x(index) > max_value
                % Set the sample to the max_value
                x(index) = max_value;
            end
        end
    end

    % Calculate the range
    Range = max_value - min_value;
    
    % Calculate the number of quantization zones
    NumberOfQuantizationZones = 2 ^ N;
    
    % Calculate the step
    Step = Range/NumberOfQuantizationZones;

    % Declare a vector that will contain the quantization zones
    centers = zeros(1, NumberOfQuantizationZones);
    
    % Calculate the first center
    centers(1) = max_value - Step/2;
    
    % For every quantization zone...
    for index = 2 : NumberOfQuantizationZones
        
        % Calculate the center
        centers(index) = centers(index - 1) - Step;
    end
    
    % Declare a vector that will contain the quantized signal
    xq = zeros(1, SignalSamples);
    
    % For every sample...
    for index = 1 : SignalSamples
        
        % Get the center with the minimum distance for the sample
        [~, position] = min(abs(centers - x(index)));
        
        % Set the quantized sample
        xq(index) = position;
    end
    
    % Transpose the quantized signal
    xq = xq';
end