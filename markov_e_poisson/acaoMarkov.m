t = 0; % tempo inicial
uInicial = 50; % preco da acao no instante inicial
tempo_total = 365; % em dias, portanto representa um ano.
rmax = 20; % representa o número de simualacoes a cada ano
et = zeros(tempo_total, rmax);
% variavel rmax vezes por simulacao
for i = 1:rmax
    u = uInicial
    % 20 simulacoes em um ano
    for j = 1:tempo_total
        u  = u + normrnd(0,1);
        et(j,i) = u;
    endfor
end
plot(et);
