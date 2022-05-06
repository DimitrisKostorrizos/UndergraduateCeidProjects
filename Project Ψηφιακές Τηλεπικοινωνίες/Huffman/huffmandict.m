function [encodings] = huffmandict(symbols, probabilities)
  
  % Declare an id for identifying the structs
  id = 0;
  
  % Initialize a struct for the node structs
  nodes = struct([]);
  
  % Ascending sort the probalities 
  [ascendingSortedProbabilities, elementIndexes] = sort(probabilities);
  
  % For every symbol...
  for index = 1 : length(ascendingSortedProbabilities)
    
    % Get the index that points to the symbol
    symbolIndex = elementIndexes(index);
        
    % Add the leaf node
    nodes(index) = struct('id', id, 'symbol', symbols(symbolIndex), 'probability', probabilities(index), 'leftChild', 0, 'rightChild', 0);
    
    % Increase the id
    id += 1;
  end
  
  % Initialize a default node for the comparisons
  defaultNode = struct('symbol', 0, 'probability', 2, 'leftChild', 0, 'rightChild', 0);
  
  % While there are at least 2 nodes...
  while length(nodes) != 1
    
    % Initialize an empty array for the structs
    remainingNodes = struct([]);
    
    % Initialize the left node
    leftNode = defaultNode;
    
    % For every node except the first...
    for(index = 1 : length(nodes))
    
      % Get the current node
      currentLeftNode = nodes(index);
      
      % If the current node probality is less than the left node...
      if(currentLeftNode.probability < leftNode.probability)
        % Update the left node
        leftNode = currentLeftNode;
      end
    end
    
    % For every node except the first...
    for(index = 1 : length(nodes))
    
      % Get the current node
      currentLeftNode = nodes(index);
      
      % If the current node symbol is the not the same as the selected left node symbol...
      if(currentLeftNode.id != leftNode.id)
        % Append the node
        remainingNodes = [remainingNodes, currentLeftNode];   
      end
    end
    
    % Update the remaining nodes
    nodes = remainingNodes;
    
    % Clear the nodes
    remainingNodes = struct([]);
    
    % Initialize the right node
    rightNode = defaultNode;
    
    % For every node except the first...
    for(index = 1 : length(nodes))
    
      % Get the current node
      currentRightNode = nodes(index);
      
      % If the current node probality is less than the right node...
      if(currentRightNode.probability < rightNode.probability)
        % Update the right node
        rightNode = currentRightNode;      
      end
    end
    
    % For every node except the first...
    for(index = 1 : length(nodes))
    
      % Get the current node
      currentRightNode = nodes(index);
      
      % If the current node symbol is the not the same as the selected right node symbol...
      if(currentRightNode.id != rightNode.id)
        % Append the node
        remainingNodes = [remainingNodes, currentRightNode]     ;   
      end
    end
    
    % Update the remaining nodes
    nodes = remainingNodes;
    
    % Calculate the probality of the new node
    sumProbability = leftNode.probability + rightNode.probability;
  
    % Initialize the new node
    treeStruct = struct('id', id, 'symbol', -1, 'probability', sumProbability, 'leftChild', leftNode, 'rightChild', rightNode);
    
    % Increase the id
    id += 1;
    
    % Prepend the new node
    nodes = [remainingNodes, treeStruct];
  end
  
  % Get the encoding for the tree
  encodings = getEncodings(nodes(1), '');
end  
