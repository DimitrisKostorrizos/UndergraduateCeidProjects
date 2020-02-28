function P = mask_band(n,type, p,varargin)
%Author: Dimitrios Kostorrizos AM: 1054419 Date: 10/12/2019
    if(nargin > 4 || nargin < 3)     
        error("Invalid number of arguments.");
    end
    if(type == "band")
        if(nargin == 3 )
            q = p;
        else       
            q = varargin{1};
        end
        P = zeros(n);
        for i = 1 : n
            for j = 1 : n
                if( i - j > p || j - i > q)
                    P(i,j) = 0;
                else
                    P(i,j) = 1;
                end
            end
        end
    else
        if(nargin ~= 3)
            error("For type btdr, you can only have 3 arguments.");
        end
        ModResidual = mod(n,p);
        Quotient = fix(n/p);
        TridiagonalMatrix = full(gallery('tridiag',Quotient,1,1,1));
        BlockOnes = ones(p);
        P = kron(TridiagonalMatrix,BlockOnes); %Kronecker Multiplication to create the block tridiagonal matrix
        if ModResidual ~= 0
            BlockR = ones(ModResidual);
            P = blkdiag(P,BlockR);
        end
    end
end