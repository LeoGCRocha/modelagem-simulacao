media_computadores = 5;
media_switch = 3;
pedido_minimo = 15;
tempo_de_simulacao = 4;
replicacao = 100000;
% Ira retornar o numero de falhas que foram obtidas em um mes
function iterator = poisson(lambda, t)
   S = [];
   tempo_simulado = 0;
   iterator = 0;
   while (tempo_simulado <= t)
     tempo_para_proximo_evento = exprnd(1/lambda);
     tempo_simulado += tempo_para_proximo_evento;
     if tempo_simulado > t;
       break
     endif
     iterator++;
   endwhile
endfunction
mes_de_sucesso = 0;
for i = 1:replicacao
  i
  lambda = media_computadores + media_switch;
  r = poisson(lambda, tempo_de_simulacao);
  if r < pedido_minimo
    mes_de_sucesso++;
  endif
endfor
if mes_de_sucesso == 0
  % nenhum mes deu sucesso
  disp("nenhum mes de sucesso")
else
  resultado = mes_de_sucesso / replicacao
endif
