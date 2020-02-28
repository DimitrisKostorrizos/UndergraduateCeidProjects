function matrix2latex2(matrix, filename, varargin)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 10/12/2019

%   - varargs is one ore more of the following (denominator, value) combinations
%      + 'rowLabels', array -> Can be used to label the rows of the
%      resulting latex table
%      + 'columnLabels', array -> Can be used to label the columns of the
%      resulting latex table
%      + 'alignment', 'value' -> Can be used to specify the alginment of
%      the table within the latex document. Valid arguments are: 'l', 'c',
%      and 'r' for left, center, and right, respectively
%      + 'format', 'value' -> Can be used to format the input data. 'value'
%      has to be a valid format string, similar to the ones used in
%      fprintf('format', value);
%      + 'size', 'value' -> One of latex' recognized font-sizes, e.g. tiny,
%      HUGE, Large, large, LARGE, etc.

%   matrix2latex(matrix, 'out.tex', 'rowLabels', rowLabels, 'columnLabels', columnLabels, 'alignment', 'c', 'format', '%-6.2f', 'size', 'tiny');
    %matrix2latex2(diag(1:3),"test.txt")
    rowLabels = [];
    colLabels = [];
    alignment = 'l';
    format = [];
    quadneeded = 0;
    textsize = [];
    if (rem(nargin,2) == 2 || nargin < 3)%%%Added the matrix type argument
        error('matrix2latex: Incorrect number of arguments to %s.', mfilename); %%%Removed ',' to correct the error message
    end
    okargs = {'rowlabels','columnlabels', 'alignment', 'format', 'size'};
    for j=1:2:(nargin-2)
        pname = varargin{j};
        if(strcmpi(pname, "tabular"))
            type = "tabular";
            k = 7;
        else
            if(strcmpi(pname, "pmatrix"))
                type = "pmatrix";
                k = 6;
            else
                if(strcmpi(pname, "bmatrix"))
                    type = "bmatrix";
                    k = 6;
                else
                    if(strcmpi(pname, "vmatrix"))
                        type = "vmatrix";
                        k = 6;
                    else
                        pval = varargin{j+1};
                        index = 1;
                        k = 0;
                        while(k == 0)
                            k = strcmpi(pname, okargs(index)); %%% Changed strmatch function to the newer version strcmpi, while removing the lower function.
                            index = index + 1;
                        end
                    end
                end
            end
        end
        if isempty(k)
            error('matrix2latex: Unknown parameter name: %s.', pname); %%%Removed ',' to correct the error message
        elseif length(k)>1
            error('matrix2latex: Ambiguous parameter name: %s.', pname); %%%Removed ',' to correct the error message
        else
            switch(k)
                case 1  % rowlabels
                    rowLabels = pval;
                    if isnumeric(rowLabels)
                        rowLabels = cellstr(num2str(rowLabels(:)));
                    end
                case 2  % column labels
                    colLabels = pval;
                    if isnumeric(colLabels)
                        colLabels = cellstr(num2str(colLabels(:)));
                    end
                case 3  % alignment
                    alignment = lower(pval);
                    if alignment == "right" %%%Changed 'right' to "right", to correct the string comparison
                        alignment = 'r';
                    end
                    if alignment == "left" %%%Changed 'left' to "left", to correct the string comparison
                        alignment = 'l';
                    end
                    if alignment == "center" %%%Changed 'center' to "center", to correct the string comparison
                        alignment = 'c';
                    end
                    if alignment ~= 'l' && alignment ~= 'c' && alignment ~= 'r'
                        alignment = 'l';
                        warning('matrix2latex: Unkown alignment. (Set it to \''left\''.)'); %%%Removed ',' to correct the error message
                    end
                case 4  % format
                    format = lower(pval);
                case 5  % format
                    textsize = pval;
                case 6 %quad tag
                    quadneeded = 1;
                case 7 %ignore tabular quad
            end
        end
    end
    fid = fopen(filename, 'w');
    width = size(matrix, 2);
    height = size(matrix, 1);
    if isnumeric(matrix)
        matrix = num2cell(matrix);
        for h=1:height
            for w=1:width
                if(~isempty(format))
                    matrix{h, w} = num2str(matrix{h, w}, format);
                else
                    matrix{h, w} = num2str(matrix{h, w});
                end
            end
        end
    end
    
    if(~isempty(textsize))
        fprintf(fid, '\\begin{%s}', textsize);
    end
    if(quadneeded == 1)
        fprintf(fid, '%s\n%s\n', "$$","\quad"); %%%Added fprintf for $$ and \quad
    end
    fprintf(fid, '\\begin{%s}{|',type); %%%Changed fprintf to print the different types
    if(~isempty(rowLabels))
        fprintf(fid, 'l|');
    end
    for i=1:width
        fprintf(fid, '%c|', alignment);
    end
    fprintf(fid, '}\r\n');%%% Removed the \\line printing
    
    if(~isempty(colLabels))
        if(~isempty(rowLabels))
            fprintf(fid, '&');
        end
        for w=1:width-1
            fprintf(fid, '\\textbf{%s}&', colLabels{w});
        end
        fprintf(fid, '\\textbf{%s}\\\\\n', colLabels{width}); %%% Removed the \\line printing
    end
    
    for h=1:height
        if(~isempty(rowLabels))
            fprintf(fid, '\\textbf{%s}&', rowLabels{h});
        end
        for w=1:width-1
            fprintf(fid, '%s&', matrix{h, w});
        end
        fprintf(fid, '%s\\\\\n', matrix{h, width});%%% Removed the \\line printing
    end
    fprintf(fid, '\\end{%s}\r\n',type); %%%Changed fprintf to print the different types
    
    if(~isempty(textsize))
        fprintf(fid, '\\end{%s}', textsize);
    end
    if(quadneeded == 1)
        fprintf(fid, '%s\n', "$$"); %%%Added fprintf for $$
    end
    fclose(fid);
end