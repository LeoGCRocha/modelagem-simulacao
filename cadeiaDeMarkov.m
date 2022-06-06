%u0 = [0.7, 0.1, 0.1, 0.1];
%T = [0.4, 0.4, 0.1, 0.1; 0.9, 0.1, 0, 0; 0.1, 0.1, 0.4, 0.4; 0 0 0.5 0.5];
%T = [0, 1, 0, 0; 0, 0, 1, 0; 0, 0, 0, 1; 1 0 0 0];

tmax = 365
rmax = 20
u0=50
et = zeros(tmax,rmax);
for r=1:1:rmax
  u = u0;
  for t=1:1:tmax
    u = u+normrnd(0, 1);
    et(t,r)=u;
  endfor
endfor
plot(et);

