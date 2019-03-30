from matplotlib import pyplot as plt
import math
import sys

plt.switch_backend('agg')

graph_name = sys.argv[1]
# label-vertex
with open('./pyplot/label-vertex.txt', mode='rt') as f:
    l=[]
    n=[]
    while True:
        text=f.readline()
        if not text:
            break
        text=text.split()
        l=l+[text[0]]
        n=n+[int(text[1])]

    plt.figure(1)
    plt.bar(l,n)
    plt.xlabel('label')
    plt.ylabel('# of vertex')
    plt.title('label-vertex')
    fig = plt.gcf()
    fpath = "./pyplot/"+str(graph_name)+"_label-vertex.png"
    fig.savefig(fpath, dpi=300)
    for i in range(len(n)):
        if n[i]!=0:
            n[i]=math.log(n[i])
    plt.figure(2)
    plt.bar(l,n)
    plt.xlabel('label')
    plt.ylabel('log(# of vertex)')
    plt.title('label-vertex')
    fig = plt.gcf()
    fpath = "./pyplot/"+str(graph_name)+"_label-vertex_log.png"
    fig.savefig(fpath, dpi=300)

