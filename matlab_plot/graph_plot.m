clc; close all;
% label
file=fopen('./label-vertex.txt', 'r');
if ( file > 0)
data = textscan(file,'%s %d');
figure(1);
label = categorical(data{1}');
vertex = data{2}';
bar(label, vertex);
title('label-vertex', 'fontsize', 14);
xlabel('label', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f1','./label-vertex', '-dpng');    

end


% degree
file=fopen('./degree.txt', 'r');
if (file>0)
d = fscanf(file, "%d");
figure(2);
histogram(d);
title('degree-vertex', 'fontsize', 14);
xlabel('degree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f2','./degree', '-dpng');
end

% indegree
file=fopen('./indegree.txt', 'r');
if(file>0)
d = fscanf(file, "%d");
figure(3);
histogram(d);
title('indegree-vertex', 'fontsize', 14);
xlabel('indegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f3','./indegree', '-dpng');

end

% outdegree
file=fopen('./outdegree.txt', 'r');
if(file>0)
d = fscanf(file, "%d");
figure(4);
histogram(d);
title('outdegree-vertex', 'fontsize', 14);
xlabel('outdegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f4','./outdegree', '-dpng');
end