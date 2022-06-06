function [encodedString, encodings, frequencies] = huffmanenco(inputString, frequencies)
  
  % If there are frequencies as input...
  if exist('frequencies','var')
    
     % Get the symbols
     symbols = frequencies(1, :);
     
     % Get the number of appearances
     numberOfAppearances = frequencies(2, :);
  else 
    % Declare an array for the symbols
    symbols = [];
    
    % Declare an array for the number a symbols appears
    numberOfAppearances = [];
    
    % Initialize an index for the symbols
    symbolIndex = 1;
    
    % For every symbol...
    for index = 1 : length(inputString)
      
      % Get the current dymbol
      currentSymbol = inputString(index);
      
      % Check whether the symbol is already in the array
      foundLetterIndex = find(symbols == currentSymbol);
      
      % If the symbol does not exist...
      if(length(foundLetterIndex) == 0)
      
        % Add it
        symbols(symbolIndex) = currentSymbol;
        
        % Initialize the number of appearances
        numberOfAppearances(symbolIndex) = 1;

        % Increase the index
        symbolIndex += 1;      
      else
        % Increase the number of appearances
        numberOfAppearances(foundLetterIndex) += 1;
      end     
    end
    
      frequencies = zeros(2, length(numberOfAppearances));
      
      % For every symbol...
      for index = 1 : length(numberOfAppearances)
          % Calculate the appearance frequency of the symbol
          numberOfAppearances(index) /= length(inputString);
        
          % Set the symbol
          frequencies(1, index) = symbols(index);
          
          % Set the frequencies
          frequencies(2, index) = numberOfAppearances(index);   
      end 
  end
  
  % Get the encodings for the symbols
  encodings = huffmandict(symbols, numberOfAppearances);
  
  % Declare a map for the encoding symbols
  encondingsSymbols = [];
    
  % Initialize an index for the encoding
  encodingIndex = 1;
  
  % Check if the input contains characters
  isChar = ischar(encodings(index));
  
  % For every encoding...
  for index = 1 : length(encodings)
    
    % If the entry is a symbol...
    if(mod(index, 2) == 1)
      % If the encoding is a character...
      if(isChar == 1)
        % Add it
        encondingsSymbols(encodingIndex) = char(encodings(index));
      else
        % Add the number
        encondingsSymbols(encodingIndex) = cell2mat(encodings(index));
      end  
    else
      % Increase the index
      encodingIndex += 1;
    end
  end
  
  % Initialize the encoded string
  encodedString = '';
  
  % For every symbol...
  for index = 1 : length(inputString)
    
    % Get the current symbol
    currentSymbol = inputString(index);
    
    % Get the index of the encoding that corresponds to the symbol
    encodingIndex = find(encondingsSymbols == currentSymbol);
    
    % Get the encoding
    encoding = encodings(encodingIndex * 2);
    
    % Added the encoded representation
    encodedString = strcat(encodedString, char(encoding));
  end
end 