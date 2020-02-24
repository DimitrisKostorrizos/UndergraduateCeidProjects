function Constellation()
    M = 4;
    symbol = zeros(1, M); 
    for i = 1:M
        symbol(i) = complex(cos((2 * pi * (i - 1)) / M), sin((2 * pi * (i - 1)) / M));
    end
    hold on
    th = 0:pi/50:2*pi;
    xunit = cos(th);
    yunit = sin(th);
    c = complex(xunit,yunit);
    plot(real(c), imag(c));
    scatter(real(symbol),imag(symbol))
    
    for i = 1:M
        textString = sprintf('(%d, %d)', round(real(symbol(i))), round(imag(symbol(i))));
        text(round(real(symbol(i))), round(imag(symbol(i))), textString, 'FontSize', 7);
    end
    title("4-PSK Constellation")
    xlabel("X");
    ylabel("Y(j)");
    grid on;
    hold off
    
    figure
    M = 8;
    symbol = zeros(1, M); 
    for i = 1:M
        symbol(i) = complex(cos((2 * pi * (i - 1)) / M), sin((2 * pi * (i - 1)) / M));
    end
    hold on
    th = 0:pi/50:2*pi;
    xunit = cos(th);
    yunit = sin(th);
    c = complex(xunit,yunit);
    plot(real(c), imag(c));
    scatter(real(symbol),imag(symbol))
    
    for i = 1:M
        textString = sprintf('(%d, %d)', round(real(symbol(i))), round(imag(symbol(i))));
        text(round(real(symbol(i))), round(imag(symbol(i))), textString, 'FontSize', 7);
    end
    title("8-PSK Constellation")
    xlabel("X");
    ylabel("Y(j)");
    grid on;
    hold off
end