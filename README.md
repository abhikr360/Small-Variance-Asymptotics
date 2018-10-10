# Small-Variance-Asymptotics for Non Parametric Bayesian Clustering

Learning the correct model size for a specific data-set is one of the biggest challenges in machine learning model. For clustering problem we need to know the number of classes. For factor analysis we need to know number of factors.

One possible way to tackle this problem is to try out several models and use the one which gives best result on validation set. Bayesian frameworks offer ways to model infinite mixture models and models in which we don't fix the number of parameters upfront. Bayesian methods offer great flexibility, for example we can even infer hierarchical models. 

Despite the huge success of Bayesian framework, simpler non-Bayesian methods such as k-means have been more popular for large scale data, due to their simplicity in implementation and high scalability. In this project, we study recent attempts to reach middle-ground using small variance asymptotics, so that we get a non parametric model which is scalable .

We start with a hard non-parametric clustering algorithm which uses Dirichlet Process. We then study an extension of this algorithm to a hierarchical structure using Hierarchical Dirichlet process. Finally, we generalize the clustering algorithm to use Bregman divergences instead of just euclidean distance. 
