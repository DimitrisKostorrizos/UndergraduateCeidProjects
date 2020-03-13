function [Xqn] = ADM(Xn, M)
    K = 1.5; %Constant K
    Step = zeros(1,length(Xn)); %Step
    Step(1) = 0.1;
    Xn = interp(Xn, M); %Hyper-Sampling Xn

    Bn = zeros(1,length(Xn));
	En = zeros(1,length(Xn));
    Xqn = zeros(1,length(Xn));
    Delay = zeros(1,length(Xn));
    Eqn = zeros(1,length(Xn));
    Delay(1) = Xn(1);
    Bn(1) = sign(Xn(1));
    Step(1) = 0.1;
    Xqn(1) = Xn(1);
    
    %Encoder
    for index = 2:length(Xn)
        En(index) = Xn(index) - Delay(index - 1);
        Bn(index) = sign(En(index)); % 1 bit Quantizer
        
        if(Bn(index) == Bn(index - 1)) % Step Control Logic
            Step(index) = Step(index - 1) * K;
        else
            Step(index) = Step(index - 1) / K;
        end
        
        Eqn(index) = Step(index) * Bn(index);
        
        Xqn(index) = Eqn(index) + Delay(index - 1);
        Delay(index) = Xqn(index);
    end    
    
    %Decoder
    for index = 2:length(Xn)
        if(Bn(index) == Bn(index - 1)) % Step Control Logic
            Step(index) = Step(index - 1) * K;
        else
            Step(index) = Step(index - 1) / K;
        end
        
        Eqn(index) = Step(index) * Bn(index);
        
        Xqn(index) = Eqn(index) + Delay(index - 1);
    end
end