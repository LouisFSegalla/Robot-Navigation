clear; clc;

pkg load control

s = tf('s')

%Parâmetros do motor
J = 0.01;
b = 0.02;
K = 0.75;
R = 5.2;
L = 1.1;

G_p = K/((J*s+b)*(L*s+R)+K^2)
x = [5.39353   48.54381    0.80142];#Kp Ki Kd

G_c = (x(3)*s*s + x(1)*s + x(2)) / s;
G_MF = minreal((G_p*G_c) / (1 + G_p*G_c));
[y1 t1 x1] = step(G_MF);
[y2 t2 x2] = step(G_p);

plot(t1,y1,'linewidth',3,'color','b',t2,y2,'linewidth',3,'color','r')
title('Resposta ao Degrau Motor CC');
legend('Malha Fechada','Malha Aberta');
grid on;
       