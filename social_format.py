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
G = ig.Graph.from_networkx(G)
#print(G.number_of_nodes())
partition = la.find_partition(G, la.ModularityVertexPartition)

print(partition)



#coms = sorted(nx_comm.louvain_communities(G),key=len,reverse=True)
#print({len(coms)})
#print(coms)