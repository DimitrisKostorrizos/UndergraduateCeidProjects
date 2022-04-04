function [encodings] = GetEncodings(rootNode, encoding)
  
  % Declare a list for the encodings
  encodings = [];
  
  % If the node is leaf one...
  if(rootNode.symbol != -1)
    % Append the encoding for the node
    encodings = [encodings, {rootNode.symbol, encoding}];
  else  
    % Get the left children
    leftPathEncodings = GetEncodings(rootNode.leftChild, [encoding, '0']);
    
    % Get the right children
    rightPathEncodings = GetEncodings(rootNode.rightChild, [encoding, '1']);
        
    % Get the encodings for the right sub tree
    encodings = [encodings, leftPathEncodings, rightPathEncodings];
  end
end