#!/usr/bin/env python3
import networkx as nx
import matplotlib.pyplot as plt
from collections import Counter
import networkx.algorithms.community as nx_comm
import igraph as ig
import leidenalg as la

#http://konect.cc/networks/twitter_mpi/

fh=open('data.moreno_highschool_highschool')
G=nx.read_weighted_edgelist(fh,comments='%',delimiter=' ',create_using=nx.DiGraph)
print(G.number_of_nodes())
G = ig.Graph.from_networkx(G)
print(G)
partition = la.find_partition(G, la.ModularityVertexPartition)

for i in range(len(partition)):
	subgraph = ig.Graph.subgraph(G, partition[i])
	print(subgraph)


print(partition)
sort_part=[]
for i in range(len(partition)):
	tempy=[]
	for j in range(len(partition[i])):
		d = G.degree(partition[i][j],mode="out")
		tempy.append((partition[i][j],d))

	tempy = sorted(tempy,reverse=True, key=lambda x: x[1])
	sort_part.append(tempy)
		#print(G.degree(partition[i][j],mode="in"))
for element in sort_part:
	print(element)

#coms = sorted(nx_comm.louvain_communities(G),key=len,reverse=True)
#print({len(coms)})
#print(coms)
