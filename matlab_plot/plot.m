%%
fileID_A=fopen('./plot/label-vertex.txt', 'r');


formatSpec = '%d';
A = fscanf(fileID_A, formatSpec);

figure(1);
histogram(A);
xlabel('label');
ylabel('# of vertex');
print('-f1','./plot/label-vertex', '-dpng');
%%
fileID_B=fopen('./plot/degree-vertex.txt', 'r');
B = fscanf(fileID_B, formatSpec);

figure(2);
histogram(B);
xlabel('degree');
ylabel('# of vertex');
print('-f2','./plot/degree-vertex', '-dpng');

