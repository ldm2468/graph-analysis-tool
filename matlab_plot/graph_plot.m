%%
clc; close all;
% label
file=fopen('./label-vertex.txt', 'r');
if ( file > 0)
data = textscan(file,'%s %f');
figure(1);
label = categorical(data{1}');
vertex = data{2}';
h=histogram('Categories', label, 'BinCounts', vertex);
h.DisplayOrder = 'descend';

title('label-vertex', 'fontsize', 14);
xlabel('label', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f1','./label-vertex', '-dpng');    
 
figure(2);
vertex_log = log10(abs(vertex));
h=histogram('Categories', label, 'BinCounts', vertex_log);
h.DisplayOrder = 'descend';
title('label-log(vertex)', 'fontsize', 14);
xlabel('label', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
print('-f2','./label-vertex_log', '-dpng');    

end
%%
% degree
file=fopen('./degree.txt', 'r');
if (file>0)
d = fscanf(file, "%f");
figure(3);
h=histogram(d);
title('degree-vertex', 'fontsize', 14);
xlabel('degree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f3','./degree', '-dpng');

figure(4);
h=histogram(log10(abs(d)));
title('degree-log(vertex)', 'fontsize', 14);
xlabel('degree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
print('-f4','./degree_log', '-dpng');

end

% indegree
file=fopen('./indegree.txt', 'r');
if(file>0)
d = fscanf(file, "%f");
figure(5);
histogram(d);
title('indegree-vertex', 'fontsize', 14);
xlabel('indegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f5','./indegree', '-dpng');
figure(6);
histogram(log10(d));
title('indegree-log(vertex)', 'fontsize', 14);
xlabel('indegree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
print('-f6','./indegree_log', '-dpng');

end

% outdegree
file=fopen('./outdegree.txt', 'r');
if(file>0)
d = fscanf(file, "%f");
figure(7);
histogram(d);
title('outdegree-vertex', 'fontsize', 14);
xlabel('outdegree', 'fontsize', 12);
ylabel('# of vertex', 'fontsize', 12);
print('-f7','./outdegree', '-dpng');
figure(8);
histogram(log10(abs(d)));
title('outdegree-log(vertex)', 'fontsize', 14);
xlabel('outdegree', 'fontsize', 12);
ylabel('log(# of vertex)', 'fontsize', 12);
print('-f8','./outdegree_log', '-dpng');
end

clc; close all;