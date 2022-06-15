pkg load statistics;
function contador_de_vendas = poisson(lambda, tempo)
  tempo_simulado = 0;
  contador_de_vendas = 0;
  S = [];
  T = [];
  while (tempo_simulado <= tempo)
    tempo_para_proximo_evento = exprnd(1/lambda);
    tempo_simulado += tempo_para_proximo_evento;
    if tempo_simulado > tempo
      break
    endif
    contador_de_vendas++;
    T(contador_de_vendas) = tempo_para_proximo_evento;
    S(contador_de_vendas) = tempo_simulado;
  endwhile
endfunction
media_vendas = 50 % a cada hora
tempo = 2 % em horas
vendas_com_sucesso = 0 
replicacoes = 10000
num_pratos = 125
for i = 1:replicacoes
  i
  r = poisson(media_vendas, tempo);
  if r > 125
    vendas_com_sucesso++;
  endif
endfor
if vendas_com_sucesso == 0
   disp("não houveram vendas com sucesso");
else
   (vendas_com_sucesso / replicacoes)*100
endif