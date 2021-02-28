function BerSerCalculations()
    
    % Delcare a matrix that will contain the BER per SNR per M, for simple
    % encoding
    % Row: M
    % Column: SNR
    SimpleEncodingBER = zeros(4,9);
    
    % Initialize an index for the M values
    MIndex = 1;
    
    % For every M...
    for M = [2, 4, 8, 16]
        
        % Initialize an index for the SNR values
        SNRIndex = 1;
        
        % For every SNR...
        for SNR = 0 : 5 : 40
            
            % Execute the MPam function and get the bit matrixes
            [OutputBitMatrix, ~, ~, InputBitMatrix] = MPam(100000, M, "Simple", SNR);
            
            % Initialize a counter for the wrong bits
            WrongBitCounter = 0;
            
            % For every symbol...
            for index = 1 : size(InputBitMatrix, 1)
                
                % For every bit...
                for secondaryIndex = 1 : size(InputBitMatrix, 2)
                    
                    % If the input bit is different then the output bit...
                    if(InputBitMatrix(index,secondaryIndex) ~= OutputBitMatrix(index,secondaryIndex))
                        
                        % Increase the counter
                        WrongBitCounter = WrongBitCounter + 1;
                    end
                end
            end
            
            % Calculate the BER 
            SimpleEncodingBER(MIndex, SNRIndex) = WrongBitCounter / size(InputBitMatrix, 1);
            
            % Increase the SNR index
            SNRIndex = SNRIndex + 1;
        end
        
        % Increase the M index
        MIndex = MIndex + 1;
    end

    % Delcare a matrix that will contain the BER per SNR per M, for Gray
    % encoding
    % Row: M
    % Column: SNR
    GrayEncodingBER = zeros(3,9);
    
    % Initialize an index for the M values
    MIndex = 1;
    
    % For every M...
    for M = [4, 8, 16]
        
        % Initialize an index for the SNR values
        SNRIndex = 1;
        
        % For every SNR...
        for SNR = 0 : 5 : 40
            
            % Execute the MPam function and get the bit matrixes
            [OutputBitMatrix, ~, ~, InputBitMatrix] = MPam(100000, M, "Gray", SNR);
            
            % Initialize a counter for the wrong bits
            WrongBitCounter = 0;
            
            % For every symbol...
            for index = 1 : size(InputBitMatrix, 1)
                
                % For every bit...
                for secondaryIndex = 1 : size(InputBitMatrix, 2)
                    
                    % If the input bit is different then the output bit...
                    if(InputBitMatrix(index,secondaryIndex) ~= OutputBitMatrix(index,secondaryIndex))
                        
                        % Increase the counter
                        WrongBitCounter = WrongBitCounter + 1;
                    end
                end
            end
            
            % Calculate the BER 
            GrayEncodingBER(MIndex, SNRIndex) = WrongBitCounter / size(InputBitMatrix, 1);
            
            % Increase the SNR index
            SNRIndex = SNRIndex + 1;
        end
        
        % Increase the M index
        MIndex = MIndex + 1;
    end
    
    % Get the values for the X Axis
    XAxis = 0 : 5 : 40;
    
    figure
    plot(XAxis,SimpleEncodingBER(1,:),'b-o',XAxis,SimpleEncodingBER(2,:),'b-+',XAxis,SimpleEncodingBER(3,:),'b-*',XAxis,SimpleEncodingBER(4,:),'b-d',XAxis,GrayEncodingBER(1,:),'r-+',XAxis,GrayEncodingBER(2,:),'r-*',XAxis,GrayEncodingBER(3,:),'r-d')
    title('BER per SNR')
    xlabel('SNR dB')
    ylabel('BER')
    axis([0 40 0 1])
    legend({'Simple Encoding, M = 2','Simple Encoding, M = 4','Simple Encoding, M = 8','Simple Encoding, M = 16','GrayEncoding, M = 4','GrayEncoding, M = 8','GrayEncoding, M = 16'},'Location','northeast')
    
    % Delcare a matrix that will contain the SER per SNR per M, for simple
    % encoding
    % Row: M
    % Column: SNR
    SimpleEncodingSER = zeros(3,9);
    
    % Initialise an index for the M values
    MIndex = 1;
    
    % For every M...
    for M = [4, 8, 16]
        
        % Initialise an index for the SNR values
        SNRIndex = 1;
        
        % For every SNR...
        for SNR = 0 : 5 : 40
            
            % Execute the MPam function and get the symbol vectors
            [~, OutputSymbolVector, InputSymbolVector, ~] = MPam(100000, M, "Simple", SNR);
            
            % Initialize a counter for the wrong symbols
            WrongSymbolCounter = 0;
            
            % For every symbol...
            for index = 1 : length(InputSymbolVector)
                
                % If the input symbol is different then the output symbol...
                if(InputSymbolVector(index) ~= OutputSymbolVector(index))

                    % Increase the counter
                    WrongSymbolCounter = WrongSymbolCounter + 1;
                end
                
            end
            
            % Calculate the SER 
            SimpleEncodingSER(MIndex, SNRIndex) = WrongSymbolCounter / length(InputSymbolVector);
            
            % Increase the SNR index
            SNRIndex = SNRIndex + 1;
        end
        
        % Increase the M index
        MIndex = MIndex + 1;
    end

    % Delcare a matrix that will contain the SER per SNR per M, for Gray
    % encoding
    % Row: M
    % Column: SNR
    GrayEncodingSER = zeros(3,9);
    
    % Initialise an index for the M values
    MIndex = 1;
    
    % For every M...
    for M = [4, 8, 16]
        
        % Initialise an index for the SNR values
        SNRIndex = 1;
        
        % For every SNR...
        for SNR = 0 : 5 : 40
            
            % Execute the MPam function and get the symbol vectors
            [~, OutputSymbolVector, InputSymbolVector, ~] = MPam(100000, M, "Gray", SNR);
           
            % Initialize a counter for the wrong symbols
            WrongSymbolCounter = 0;
            
            % For every symbol...
            for index = 1 : length(InputSymbolVector)
                
                % If the input symbol is different then the output symbol...
                if(InputSymbolVector(index) ~= OutputSymbolVector(index))

                    % Increase the counter
                    WrongSymbolCounter = WrongSymbolCounter + 1;
                end
                
            end
            
            % Calculate the SER 
            GrayEncodingSER(MIndex, SNRIndex) = WrongSymbolCounter / length(InputSymbolVector);
            
            % Increase the SNR index
            SNRIndex = SNRIndex + 1;
        end
        
        % Increase the M index
        MIndex = MIndex + 1;
    end
    
    % Get the values for the X Axis
    XAxis = 0 : 5 : 40;
    
    figure
    plot(XAxis,SimpleEncodingBER(2,:),'b-+',XAxis,SimpleEncodingBER(3,:),'b-*',XAxis,SimpleEncodingBER(4,:),'b-d',XAxis,GrayEncodingBER(1,:),'r-+',XAxis,GrayEncodingBER(2,:),'r-*',XAxis,GrayEncodingBER(3,:),'r-d')
    title('SER per SNR')
    xlabel('SNR dB')
    ylabel('SER')
    axis([0 40 0 1])
    legend({'Simple Encoding, M = 4','Simple Encoding, M = 8','Simple Encoding, M = 16','GrayEncoding, M = 4','GrayEncoding, M = 8','GrayEncoding, M = 16'},'Location','northeast')
end