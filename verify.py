import sys
from Bio import Phylo
from cStringIO import StringIO
from Bio.Phylo.TreeConstruction import DistanceMatrix
from Bio.Phylo.TreeConstruction import DistanceTreeConstructor

if (len(sys.argv) != 3):
	print("Arguments must be presented in the following way.")
	print("python " + sys.argv[0] + " <input-file> <output-file>")
	sys.exit(1)


fi = open(sys.argv[1],'r')
fl = fi.readlines()

n = int(fl.pop(0))

names = [chr(i) for i in range(ord('A'), ord('A')+n)]
matrix = [[float(fl.pop(0)) for j in range (i)] + [0] for i in range(n)]

dm = DistanceMatrix(names, matrix)
print(dm)

constructor = DistanceTreeConstructor()
tree_0 = constructor.upgma(dm)
print('ascii tree from biopython')
Phylo.draw_ascii(tree_0)

fo = open(sys.argv[2],'r')
treeData = fo.readline()
handle = StringIO(treeData)
tree_1 = Phylo.read(handle, 'newick')

print('ascii tree from our code')
Phylo.draw_ascii(tree_1)

