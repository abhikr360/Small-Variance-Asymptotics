# constants
# VOCAB = 53975
# DOCS = 11269
# SET_SIZE = 2250
# SETS = 5

# for minitrain
VOCAB = 893
DOCS = 5
SET_SIZE = 1
SETS = 5

import numpy as np


# data_file_name = './matlab/train.data'
# label_file_name = './matlab/train.label'
# out_file_name = './matlab/train_processed.data'
# out_label_file_name = './matlab/train_processed.label'

# for minitrain
data_file_name = './matlab/minitrain.data'
label_file_name = './matlab/minitrain.label'
out_file_name = './matlab/minitrain_processed.data'
out_label_file_name = './matlab/minitrain_processed.label'


data_file = open(data_file_name, 'r')
label_file = open(label_file_name, 'r')
out_file = open(out_file_name, 'w')
out_label_file = open(out_label_file_name, 'w')

data = data_file.read().split('\n')
labels = label_file.read().split('\n')

data = data[:-1]
labels = labels[:-1]

for i in range(len(data)):
	data[i] = data[i].split()
	for j in range(3):
		data[i][j] = int(data[i][j])

# for i in range(len(labels)):
# 	labels[i] = int(labels[i])

documents = np.zeros((DOCS, VOCAB))

for i in range(len(data)):
	doc = data[i][0] - 1
	word = data[i][1] - 1
	count = data[i][2]

	documents[doc, word] = count

# print(documents)
_y = np.arange(DOCS)

np.random.shuffle(_y)

counter = 0
for i in range(DOCS):
	if(counter % SET_SIZE == 0):
		counter = 0
		out_file.write("-1\n")
		out_label_file.write("-1\n")


	doc = _y[i]
	for word in range(VOCAB):
		if(int(documents[doc, word]) != 0):
			out_file.write("{} {} {}\n".format(counter, word, int(documents[doc, word])))
	out_label_file.write("{}\n".format(labels[i]))
	counter += 1


