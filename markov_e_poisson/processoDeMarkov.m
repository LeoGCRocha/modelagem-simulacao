espaco_de_estados = [0, 1, 2, 3];
u0 = [0.7 0.1 0.1 0.1] %distrubuicao inicial
T = [0.1 0.7 0.1 0.1; 0.1 0.1 0.7 0.1; 0.1 0.1 0.1 0.7; 0.7 0.1 0.1 0.1]; % matriz de transicao
% u1 = u0*T
% Para calcular u2 basta multiplicar u1*T
% Para calcular u(n) basta multiplcoar u0*T^n
% Exemplo de Calculo até alcançar o estado estacionário
ux = [-1 -1 -1 -1]
un = [9999 9999 9999 9999]
n = 1
while true
  if (ux==un)
    disp("alcancou o processo estacionario")
    disp(n)
    break
  else
    ux = un
    un = u0*T^n
    n = n + 1
  endif
endwhile
