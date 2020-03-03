function BerSer(N)
    index = 1;
    BER4 = zeros(1,16);
    SER4 = zeros(1,16);
    for SNR = 0:2:30
        [OutputBitMatrix,OutputSymbolVector,InputSymbolVector,InputBitMatrix] = PSK(N, 4, "ideal",SNR);

        %BER Calculation
        counter = 0;
        for i = 1 : size(InputBitMatrix,1)
            for j = 1: size(InputBitMatrix,2)
                if OutputBitMatrix(i,j) ~= InputBitMatrix(i,j)
                    counter = counter + 1;
                end
            end
        end
        BER4(index) = counter/(size(InputBitMatrix,1) * size(InputBitMatrix,2));

        %SER Calculation
        counter = 0;
        for i = 1 : length(InputSymbolVector)
            if OutputSymbolVector(i) ~= InputSymbolVector(i)
                counter = counter + 1;
            end
        end
        SER4(index) = counter/length(InputSymbolVector);
        index = index + 1;
    end
    
    index = 1;
    SER8 = zeros(1,16);
    BER8 = zeros(1,16);
    for SNR = 0:2:30
        [OutputBitMatrix,OutputSymbolVector,InputSymbolVector,InputBitMatrix] = PSK(N,8,"ideal",SNR);

        %BER Calculation
        counter = 0;
        for i = 1 : size(InputBitMatrix,1)
            for j = 1: size(InputBitMatrix,2)
                if OutputBitMatrix(i,j) ~= InputBitMatrix(i,j)
                    counter = counter + 1;
                end
            end
        end
        BER8(index) = counter/(size(InputBitMatrix,1) * size(InputBitMatrix,2));

        %SER Calculation
        counter = 0;
        for i = 1 : length(InputSymbolVector)
            if OutputSymbolVector(i) ~= InputSymbolVector(i)
                counter = counter +1;
            end
        end
        SER8(index) = counter/length(InputSymbolVector);
        index = index + 1;
    end
	
	index = 1;
    NIBER4 = zeros(1,16);
    NISER4 = zeros(1,16);
    for SNR = 0:2:30
        [OutputBitMatrix,OutputSymbolVector,InputSymbolVector,InputBitMatrix] = PSK(N, 4, "non-ideal",SNR);

        %BER Calculation
        counter = 0;
        for i = 1 : size(InputBitMatrix,1)
            for j = 1: size(InputBitMatrix,2)
                if OutputBitMatrix(i,j) ~= InputBitMatrix(i,j)
                    counter = counter + 1;
                end
            end
        end
        NIBER4(index) = counter/(size(InputBitMatrix,1) * size(InputBitMatrix,2));

        %SER Calculation
        counter = 0;
        for i = 1 : length(InputSymbolVector)
            if OutputSymbolVector(i) ~= InputSymbolVector(i)
                counter = counter + 1;
            end
        end
        NISER4(index) = counter/length(InputSymbolVector);
        index = index + 1;
    end
    
    index = 1;
    NISER8 = zeros(1,16);
    NIBER8 = zeros(1,16);
    for SNR = 0:2:30
        [OutputBitMatrix,OutputSymbolVector,InputSymbolVector,InputBitMatrix] = PSK(N,8,"non-ideal",SNR);

        %BER Calculation
        counter = 0;
        for i = 1 : size(InputBitMatrix,1)
            for j = 1: size(InputBitMatrix,2)
                if OutputBitMatrix(i,j) ~= InputBitMatrix(i,j)
                    counter = counter + 1;
                end
            end
        end
        NIBER8(index) = counter/(size(InputBitMatrix,1) * size(InputBitMatrix,2));

        %SER Calculation
        counter = 0;
        for i = 1 : length(InputSymbolVector)
            if OutputSymbolVector(i) ~= InputSymbolVector(i)
                counter = counter +1;
            end
        end
        NISER8(index) = counter/length(InputSymbolVector);
        index = index + 1;
    end
    figure
    plot(0:2:30,BER4,'g:d', 0:2:30,NIBER4,'g:+', 0:2:30,BER8,'b--d', 0:2:30,NIBER8,'b--+','MarkerSize',15);
    title("BER per SNR")
    xlabel("SNR");
    ylabel("BER");
    legend({'M = 4 PSK Ideal Channel', 'M = 4 PSK Non-Ideal Channel','M = 8 PSK Ideal Channel', 'M = 8 PSK Non-Ideal Channel'},'Location','eastoutside')

	
    figure
    plot(0:2:30,SER4,'g:d', 0:2:30,NISER4,'g:+', 0:2:30,SER8,'b--d', 0:2:30,NISER8,'b--+','MarkerSize',15);
    title("SER per SNR")
    xlabel("SNR");
    ylabel("SER");
    legend({'M = 4 PSK Ideal Channel', 'M = 4 PSK Non-Ideal Channel','M = 8 PSK Ideal Channel', 'M = 8 PSK Non-Ideal Channel'},'Location','eastoutside')
end