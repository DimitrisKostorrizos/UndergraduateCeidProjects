#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int EncodingIndex = 0;

struct Encoding* Encodings[24];

struct Node 
{
    char data;

    double frequency;

    struct Node *left, *right;
};

struct Node* newNode(char data, double frequency)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    temp->left = temp->right = NULL;
    
    temp->data = data;
    
    temp->frequency = frequency;

    return temp;
}

struct Encoding
{
    char data;
    
    char* encoding;
    
    double frequency;
};

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

int isLeafNode(struct Node* root)
{
    return !(root->left) && !(root->right);
}

struct Node* buildHuffmanTree(char* input)
{
    int numberOfCharacters = strlen(input);

    int numberOfLetters = 24;

    int nextAvailablePosition = 0;

    char greekLetters[numberOfLetters];

    double frequences[numberOfLetters];

    for(int i = 0; i < strlen(input); i++)
    {
        int isMapped = 0;

        char currentSymbol = input[i];
        
        for(int j = 0; j < numberOfLetters; j++)
        {
            if(greekLetters[j] == currentSymbol)
            {
                frequences[j] += 1;

                isMapped = 1;
            }
        }

        if(isMapped == 0)
        {
            greekLetters[nextAvailablePosition] = currentSymbol;

            frequences[nextAvailablePosition] = 1;

            nextAvailablePosition++;
        }
    }

    struct Node* Nodes[numberOfLetters];

    for(int i = 0; i < nextAvailablePosition; i++)
        Nodes[i] = newNode(greekLetters[i], frequences[i] / numberOfCharacters);

    struct Node *left, *right, *parent;
    
    int isCompleted = 0;

    while (isCompleted == 0) 
    {
        isCompleted = 1;

        double maximumFrequency = 2;

        int position;

        for(int i = 0; i < nextAvailablePosition; i++)
        {
            if(Nodes[i] == NULL)
                continue;

            if(Nodes[i]->frequency < maximumFrequency)
            {
                left = Nodes[i];

                maximumFrequency = left->frequency;

                position = i;
            }
        }

        Nodes[position] = NULL;

        maximumFrequency = 2;

        for(int i = 0; i < nextAvailablePosition; i++)
        {
            if(Nodes[i] == NULL)
                continue;

            if(Nodes[i]->frequency < maximumFrequency)
            {
                right = Nodes[i];

                maximumFrequency = right->frequency;

                position = i;
            }
        }

        Nodes[position] = NULL;

        parent = newNode('*', left->frequency + right->frequency);

        parent->left = left;
        parent->right = right;

        for(int i = 0; i < nextAvailablePosition; i++)
        {
            if(Nodes[i] != NULL)
                isCompleted = 0;
        }
        
        Nodes[position] = parent;
    }

    for(int i = 0; i < nextAvailablePosition; i++)
    {
        if(Nodes[i] != NULL)
            return Nodes[i];
    }
    
    return NULL;
}

void printEncodings(struct Node* root, int arr[], int parent)
{
    if (root->left) 
    {
        arr[parent] = 0;

        printEncodings(root->left, arr, parent + 1);
    }

    if (root->right) 
    {
        arr[parent] = 1;

        printEncodings(root->right, arr, parent + 1);
    }

    if (isLeafNode(root)) 
    {
        printf("%c: ", root->data);

        printArray(arr, parent);
    }
}

void initializeEncodings(struct Node* root, char* encoding)
{
    if (root->left) 
        initializeEncodings(root->left, strcat(strdup(encoding), "0"));

    if (root->right) 
        initializeEncodings(root->right, strcat(strdup(encoding), "1"));
    
    if(isLeafNode(root))
    {
        struct Encoding* temp = (struct Encoding*)malloc(sizeof(struct Encoding));
        
        temp->data = root->data;
        
        temp->encoding = encoding;
        
        temp->frequency = root->frequency;
        
        Encodings[EncodingIndex] = temp;
        
        EncodingIndex++;
        
        return;
    }
    
    return;
}

char* encode(char* input)
{
    char* encodedString = "";
        
    char* encoding = "";
    
    for(int i = 0; i < strlen(input); i++)
    {
        char currentSymbol = input[i];

        for(int j = 0; j < EncodingIndex; j++)
        {
            if(Encodings[j]->data == currentSymbol)
                encoding = Encodings[j]->encoding;
        }

        char* copy = strcat(strdup(encodedString), encoding);
        
        encodedString = strdup(copy);
        
        free(copy);
    }

    return encodedString;
}

char* decode(char* input)
{
    char* decodedString = "";
    
    int encodedStringLength = strlen(input);
    
    int startingSymbolIndex = 0;
    
    int endingSymbolIndex = startingSymbolIndex;
    
    while (startingSymbolIndex < encodedStringLength)
    {
        int isMapped = 0;
        
        int substringLength = endingSymbolIndex - startingSymbolIndex + 1;
        
        int nullTerminatedSubstringLength = substringLength + 1;
        
        char substr[nullTerminatedSubstringLength];
        
        memcpy(substr, &input[startingSymbolIndex], substringLength);
        
        substr[substringLength] = '\0';
        
        for(int j = 0; j < EncodingIndex; j++)
        {
            if(strcmp(substr, Encodings[j]->encoding) == 0)
            {
                char character = Encodings[j]->data;
                
                isMapped = 1;
                
                char *temp;
                
                asprintf(&temp, "%s%c", decodedString, character);
                
                decodedString = strdup(temp);
                
                free(temp);
                
                startingSymbolIndex = endingSymbolIndex + 1;
                
                endingSymbolIndex = startingSymbolIndex;
            }
        }
        
        if(isMapped == 0)
            endingSymbolIndex++;
    }

    return decodedString;
}

int main()
{
    char* text = "abcdefghii";
    
    printf("Input: %s\n", text);
    
    struct Node* root = buildHuffmanTree(text);

    int code[24];

    printEncodings(root, code, 0);
    
    char* encoding = "";

    initializeEncodings(root, encoding);
    
    char* encoded = encode(text);

    printf("Encoded: %s\n", encoded);
    
    char* decoded = decode(encoded);

    printf("Decoded: %s\n", decoded);
    
    int uncompressedDataSizeInBits = strlen(text) * 8;
    
    int compressedDataSizeInBits = 0;
    
    for(int j = 0; j < EncodingIndex; j++)
        compressedDataSizeInBits += Encodings[j]->frequency * strlen(text) * strlen(Encodings[j]->encoding);
        
    double compressionRation = (compressedDataSizeInBits * 100) /uncompressedDataSizeInBits;
    
    printf("Compression Ration: %.2f %%", compressionRation);
    
    return 0;
}