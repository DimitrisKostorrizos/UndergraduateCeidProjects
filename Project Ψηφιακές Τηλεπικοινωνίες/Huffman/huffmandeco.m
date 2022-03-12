function [output] = huffmandeco(encodedString, encodings)
  
  % Declare a list for the symbols
  encondingsSymbols = [];
  
  % Declare a map for the encodings
  encondingsRepresentation = {};
  
  % Initialize an index for the encoding
  encodingIndex = 1;
  
  % For every encoding...
  for index = 1 : length(encodings)
    
    % If the entry is a symbol...
    if(mod(index, 2) == 1)
      % Add it
      encondingsSymbols(encodingIndex) = char(encodings(index));
    else
      encondingsRepresentation(encodingIndex) = char(encodings(index));
      
      % Increase the index
      encodingIndex += 1;
    end
  end
  
  % Initialize the output
  output = '';
  
  % Initialize the starting symbol index
  startingSymbolIndex = 1;
  
  % Initialize the ending symbol index
  endingSymbolIndex = startingSymbolIndex;
  
  % While there are characters...
  while startingSymbolIndex < length(encodedString)
    
    % Get the current symbol representation
    currentSymbol = encodedString(startingSymbolIndex : endingSymbolIndex);
    
    % Initialize the symbol index
    symbolIndex = 0;
    
    % For every node except the first...
    for(index = 1 : length(encondingsRepresentation))
    
      % Get the current node
      encondingRepresentation = encondingsRepresentation(index);
      
      % If the current node probality is less than the left node...
      if(strcmp(encondingRepresentation, currentSymbol) == 1)
        % Update the left node
        symbolIndex = index;      
      end
    end
    
    % If the symbol was not matched...
    if(symbolIndex == 0)
      % Get the next bit
      endingSymbolIndex += 1;
    else
      % Get the encoding
      symbol = encondingsSymbols(symbolIndex);
      
      % If the charcter was the white space...
      if(symbol == 32)
        % Add it like this
        output = strcat(output, {' '}, symbol);
      else
        % Added the encoded representation
        output = strcat(output, symbol);      
      end

      % Point to the next character
      startingSymbolIndex = endingSymbolIndex + 1;

      % Point to the next character
      endingSymbolIndex = startingSymbolIndex;
    end
  end
end