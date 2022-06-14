tempo_total = 8;
lambda = 2;
function [S,T] = poisson(lambda, t)
   tempo_simulado = 0;
   contador_de_eventos = 0;
   while (tempo_simulado <= t)
     tempo_para_proximo_evento = exprnd(1/lambda);
     tempo_simulado += tempo_para_proximo_evento;
     if tempo_simulado > t;
       break
     endif
     contador_de_eventos++;
     S(contador_de_eventos) = tempo_simulado;
     T(contador_de_eventos) = tempo_para_proximo_evento;
   endwhile
endfunction
[S, T] = poisson(lambda, tempo_total);
plot([S,T]);