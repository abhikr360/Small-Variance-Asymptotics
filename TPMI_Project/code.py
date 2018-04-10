import numpy as np
import pickle
import scipy.io


# mat = scipy.io.loadmat('nips12raw_str602.mat')
# X = mat['counts']
# X =X.T
# X = X[:5]


# X = pickle.load(open('featureVector', 'rb'))
X = pickle.load(open('miniFeat', 'rb'))



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
	cluster_centers = np.zeros((1,X[0].shape[0]))
	cluster_centers[0] = X[0]
	epochs=20


	# print("updating cluster assignment")
	'''
		updating cluster assignment
	'''
	for e in range(epochs):
		for i in range(X.shape[0]):
			x= X[i]
			# print(x)

			temp = cluster_centers - x
			# print(temp)

			temp = np.square(temp)
			# print(temp)

			temp = np.sum(temp, axis=1)
			# print(temp)

			c = np.argmin(temp)

			# print(c)
			if temp[c] > lamda:
				k=k+1
				z[i]=k
				# print(cluster_centers.shape, x.shape)
				cluster_centers=np.vstack((cluster_centers, x.reshape(1,x.shape[0])))
				# print(cluster_centers)
			else:
				z[i]=c


	# print(".... Clusters successfully assigned ....")


	'''
		updating clusters
	'''
	z = z.astype(int)
	# print(z)
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
		

for lamda in range(10, 20000, 10):
	print( lamda, DP_means(lamda=lamda))
