fileID_A=fopen('./label-vertex.txt', 'r');
formatSpec = '%d';
A = fscanf(fileID_A, formatSpec);
figure(1);
histogram(A);
title('label-vertex');
xlabel('label');
ylabel('# of vertex');
print('-f1','./label-vertex', '-dpng');

fileID_B=fopen('./degree-vertex.txt', 'r');
B = fscanf(fileID_B, formatSpec);
figure(2);
histogram(B);
title('degree-vertex');
xlabel('degree');
ylabel('# of vertex');
print('-f2','./degree-vertex', '-dpng');

