function MFSKCalculation(N)
  
  % Initialize the N
  N = 100000;
  
  % Initialize the M values
  MValues = [2, 4, 8];
  
  % Initialize the SNR
  SNRValues = [0 : 5 : 40];
  
  % Declare a matrix for the BER
  BERValues = zeros(3, 9);
  
  % Declare a matrix for the SER
  SERValues = zeros(2, 9);
  
    % For every M...
  for MIndex = 1 : length(MValues)
    
    % Get the M
    M = MValues(MIndex);
    
    % For every SNR...
    for SNRIndex = 1 : length(SNRValues)
      
      % Get the SNR
      SNR = SNRValues(SNRIndex);
      
      % Execute the M-FSK
      [OutputBitMatrix, OutputSymbolVector, InputSymbolVector, InputBitMatrix] = MFSK(N, M, SNR);
      
      % Initialize the BER counter
      berCounter = 0;
      
      % For every row...
      for row = 1 : size(InputBitMatrix, 1)
          % For every column...
          for column = 1 : size(InputBitMatrix, 2)
              % If the bit is different...
              if OutputBitMatrix(row, column) ~= InputBitMatrix(row, column)
                  % Increase the BER counter
                  berCounter += 1;
              end
          end
      end
      
      % Add the BER
      BERValues(MIndex, SNRIndex) = berCounter / (size(InputBitMatrix, 1) * size(InputBitMatrix, 2));
      
      % If the M is either 4 or 8...
      if(M == 4 || M == 8)
      
        % Initialize the BER counter
        serCounter = 0;
        
        % For every symbol...
        for index = 1 : length(InputSymbolVector)
            % If the symbol is different...
            if InputSymbolVector(index) ~= OutputSymbolVector(index)
                % Increase the SER counter
                serCounter += 1;
            end
        end
        
        % Add the SER
        SERValues(MIndex - 1, SNRIndex) = serCounter / length(OutputSymbolVector);
      end
    end
  end  
  
  figure
  semilogy(SNRValues, BERValues(1, :), 'g', SNRValues, BERValues(2, :), 'b', SNRValues, BERValues(3, :), 'r', 'MarkerSize', 20);
  title("BER бн№ SNR")
  xlabel("SNR");
  ylabel("BER");
  legend({'M = 2 FSK', 'M = 4 FSK', 'M = 8 FSK'}, 'Location', 'eastoutside')  
  
  figure
  semilogy(SNRValues, SERValues(1, :), 'g', SERValues, SERValues(2, :), 'r', 'MarkerSize', 20);
  title("SER бн№ SNR")
  xlabel("SNR");
  ylabel("SER");
  legend({'M = 4 FSK', 'M = 8 FSK'}, 'Location', 'eastoutside')
end