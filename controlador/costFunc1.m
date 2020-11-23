function out=costFunc1(coef,s)

  Kp     = coef(1);
  Ti     = coef(2);
  Td     = coef(3);
  %lambda = coef(4);
  %mi     = coef(5);

  %forçando a serem 1 para garantir um PID de ordem inteira
  lambda = 1;
  mi     = 1;
  
  Gp = 1 / ((s+1)*(s^2 + 1));
  
  
  G = 1 + ((Kp + (Ti/s.^(lambda)) + Td*s.^mi) * Gp);

  R   = real(G);
  I   = imag(G);
  F   = atan(I/R);
  out = abs(R) + abs(I) + abs(F);
end