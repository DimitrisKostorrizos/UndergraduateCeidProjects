function [Xq, Centers ,D] = LloydMax(X, N, Xmin, Xmax)
    EncodingLength = 2 ^ N;
    Columns = length(X); %Number of Signal Samples
    step = (Xmin - Xmax)/EncodingLength;
    middle_point = mean(X);
    Centers = zeros(1, EncodingLength);
    for index = 1: EncodingLength /2
        Centers(EncodingLength/2 + 1 - index) = middle_point + index*step;
        Centers(EncodingLength/2 + index) = middle_point - index*step;
    end  

    D = [0,1]; %Signal Distortion Array
    K = 2;
    Xq = zeros(1, Columns);

    while (abs(D(K) - D(K-1)) > eps)
        ElementsSum = 0;
        
        CountedElements   = zeros(1, length(Centers));
        ConditionalMean = zeros(1, length(Centers));

        % Calculating the quantization zones.
        T = zeros(1, EncodingLength);
        for index = 1:(length(Centers)-1)
            T(index) = (Centers(index) + Centers(index+1))/2;
        end


        for index = 1:Columns %Iterating over the signal.
            for counter = 1:(length(T)-1) %Iterating over the zones to find the correct one.
                if T(counter) < X(index) && X(index) <= T(counter+1)
                    % The result.
                    Xq(index) = T(counter);
                    % We need to calculate the mean distance from the center.
                    ElementsSum = ElementsSum + abs(Centers(counter+1) - X(index));
                    % We also need to find the conditional mean for the next zones.
                    ConditionalMean(counter) = ConditionalMean(counter) + X(index);
                    CountedElements(counter)   = CountedElements(counter) + 1;
                end
            end
            % Edge case of a data point directly on the min bound.
            if X(index) == T(1)
                % Almost the same as above.
                Xq(index) = T(1);
                ElementsSum = ElementsSum + abs(Centers(2) - X(index));
                ConditionalMean(1) = ConditionalMean(1) + X(index);
                CountedElements(1)   = CountedElements(1) + 1;
            end
        end
		
		%Calculate the average distortion.
        AverageDistortion = ElementsSum/Columns;
        K = K + 1;
        D(K) = AverageDistortion;

        % Finding the new Centers, to get the next zones.
        for counter = 2:(length(Centers)-1)
            if CountedElements(counter-1) ~= 0
                Centers(counter) = ConditionalMean(counter-1)/CountedElements(counter-1);
            end
        end
    end
end