disp("gogogo");

function valor = sorteioRandom(u)
   r = rand();
   soma = 0;
   pos = 1;
   do
     valor = pos;
     soma += u(pos);
     pos++;
   until r <= soma;
endfunction


u0 = [0.7, 0.1, 0.1, 0.1];
T = [0.4, 0.4, 0.1, 0.1; 0.9, 0.1, 0, 0; 0.1, 0.1, 0.4, 0.4; 0 0 0.5 0.5];
%T = [0, 1, 0, 0; 0, 0, 1, 0; 0, 0, 0, 1; 1 0 0 0];
r= 1000;
et = zeros(r,1);
u = u0;
for t=1:1:r
  e = sorteioRandom(u);
  et(t,1)=e;
  %disp(e);
  u = T(e,:);
endfor
plot(et);


