function [SQNR, Kmax, CentersProbabilities] = LloydMaxCalculations()
    
    % Read the speech.wav
    [x,~]= audioread('speech.wav');
    
    % Initialize the min_value to -1
    min_value = -1;
    
    % Initialize the max_value to 1
    max_value = 1;
    
    % Initialize an index for the N values
    NIndex = 1;
    
    % Declare a vector the will contain the SQNR
    SQNR = zeros(1, 3);
    
    % Declare a vector the will contain the Kmax
    Kmax = zeros(1, 3);
    
    % Declare a vector the will contain the center probabilities
    CentersProbabilities = cell(1, 3);
    
    % For every N...
    for N = [2, 4, 6]
        
        % Execute the Lloyd Max function
        [Xq, Centers ,D] = LloydMax(x, N, min_value, max_value);
        
        % Declare a vector the will contain the quantization counts
        QuantizationCounts = zeros(1, length(Centers));
        
        % Declare a vector the will contain the minimum distance
        MinimumDistance = zeros(1, length(Centers));
        
        % For every sample...
        for index = 1 : length(x)

            % For every center...
            for secondaryIndex = 1 : length(Centers)
                
                % Calculate the minimum distance for every sample
                MinimumDistance(secondaryIndex) = abs(x(index) - Centers(secondaryIndex));
            end
            
            % Get the position of the minimum value
            [~, position] = min(MinimumDistance);
            
            % Increase the quantization count of that center
            QuantizationCounts(position) = QuantizationCounts(position) + 1;
        end
        
        % Calculate the center probalities
        CentersProbabilities(NIndex) = {QuantizationCounts/length(x)};
        
        % Calculate the SQNR
        SQNR(NIndex) = 10 * log10(sum(Xq.^2) / sum((Xq - x).^2));
        
        % Calculate the kmax
        Kmax(NIndex) = length(D);
        
        % Increase the N index
        NIndex = NIndex + 1;
    end
    
    figure
    plot(Kmax,SQNR,'b-+')
    title('SQNR per Kmax')
    xlabel('Kmax')
    ylabel('SQNR')
end