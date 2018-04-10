import numpy as np
import pickle
import scipy.io
import scipy.sparse

X = scipy.io.loadmat('matlab/train.data')
# X = mat['counts']
# X =X.T
# X = X[:5]


# X = pickle.load(open('featureVector', 'rb'))
# X = pickle.load(open('miniFeat', 'rb'))

print(X.shape)
print(type(X))
print(X[0].shape)
print(X[0])
X = X.astype(int)
print(type(X[0,0]))
# np.savetxt("foo.csv", X, delimiter="\t")
# f = open("foo.csv", 'w')
# np.savetxt(f, X, fmt='%i', delimiter="\t")


exit()

# X = np.array(([[1,2,3],[0,1,0],[5,6,7],[8,9,0],[0,0,0]]))

def print_clusters(z):
	k=len(set(z))
	for i in range(k):
		t = np.where(z == i)[0]
		print('.. Cluster ', i, '------------')
		print(t)


def DP_means(lamda):

	# print(".... Using DP Means with euclidean ....")
	'''
	Initialization
	'''
	k=0
	z=np.zeros(X.shape[0])
	# print(X[0].shape)
	# cluster_centers = np.zeros(X[0].shape)
	# print(cluster_centers.shape)
	cluster_centers = X[0]
	epochs=20


	# print("updating cluster assignment")
	'''
		updating cluster assignment
	'''
	for e in range(epochs):
		for i in range(X.shape[0]):
			tx= X[i]
			x = X[i]
			# print(x.toarray()[0])
			# print(type(x), type(cluster_centers))
			# print(cluster_centers)
			# for l in range(cluster_centers.shape[0]-tx.shape[0]):
			# 	x=scipy.sparse.vstack([x, tx])
			# print(x.shape, cluster_centers.shape, "...")
			temp = cluster_centers[:]
			for i in range(cluster_centers.shape[0]):
				temp[i] = cluster_centers[i] - x
			# print(temp)
			# print type(temp)

			temp = temp.power(2)
			# print(temp)

			temp = temp.sum(axis=1)
			# print(temp)

			c = temp.argmin()
			# print("c", c)
			# exit()
			if temp[c] > lamda:
				k=k+1
				z[i]=k
				# print("k", k)
				cluster_centers=scipy.sparse.vstack([cluster_centers, tx])
				# print(cluster_centers.shape)
			else:
				z[i]=c
			print('.......... %d ......\r'%(i)),
		print("Finished epoch %s\r"%(e)),


	# print(".... Clusters successfully assigned ....")


	'''
		updating clusters
	'''
	z = z.astype(int)
	# print(z)
	# print(k)
	clustercount = np.zeros(k+1)
	# print(clustercount.shape, cluster_centers.shape)
	for i in range(X.shape[0]):
		# print(z[i], i)
		cluster_centers[z[i]] += X[i]
		clustercount[z[i]] += 1

	# print(clustercount)
	for j in range(cluster_centers.shape[0]):
		cluster_centers[j]=(1.0*cluster_centers[j])/clustercount[j]


	# print("No. of clusters",  k+1)
	# print_clusters(z)
	return k+1
		
# lamda=10
for lamda in range(50, 20000, 1000):
	print( lamda, DP_means(lamda=lamda))
