#include<iostream>
#include <vector>
#include<cstdlib>
#include<climits>
using namespace std;


#define pb push_back
#define ll long long int

// #define DOCS 5
// #define VOCAB 893
// #define LINES 1000
// #define LAMBDA 10000
// #define LAMBDA LLONG_MAX

#define N_DATASETS 8
#define EPOCHS 10
#define DOCS 11269//5
#define VOCAB 53975//893
#define LINES 1467345//1000
#define LAMBDA_L 10000
#define LAMBDA_G 10000

ll **data;
ll* clusterid;

vector<ll*> global_means;
vector<ll*> local_means[N_DATASETS];

ll n_global_clusters;
ll n_local_clusters[N_DATASETS];




void show_array(ll* arr, ll size){
	for (ll i=0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
	return;
}


void readinput(){
	data = (ll**)malloc(DOCS*sizeof(ll*));
	for (ll i = 0; i < DOCS; ++i)
	{
		data[i] = (ll*)malloc(VOCAB*sizeof(ll));
		for (ll j = 0; j < VOCAB; ++j)
		{
			data[i][j]=0;
		}
	}

	ll docid, wordid, count;
	for (ll i = 0; i < LINES; ++i)
	{
		cin >> docid; cin >> wordid; cin >> count;
		data[docid-1][wordid-1] = count;
	}

	clusterid = (ll*)malloc(DOCS*sizeof(ll));
	for (ll i = 0; i < DOCS; ++i)
	{
		clusterid[i]=0;
	}

	// Initialize
	ll* _mean = (ll*)malloc(VOCAB*sizeof(ll));
	for (ll i = 0; i < VOCAB; ++i)
	{
		_mean[i] = data[0][i];
	}
	means.pb(_mean);
	n_clusters=1;

}




ll compute_distance(ll docid, ll clusterid){
	ll d =0;
	ll temp;

	for (ll i = 0; i < VOCAB; ++i)
	{
		temp = (data[docid][i]- means[clusterid][i]);
		d += temp*temp;
		if(d > LLONG_MAX - 10000){
			cout << "d may exceed the limit .............................................. " << docid << " " <<  clusterid << "\n";
			exit(1);
		}
	}
	return d;
}



void updateMeans(ll epoch){
	ll clustercount;

	for (ll i = 0; i < n_clusters; ++i)
	{	
		cout<< "\r" << "cluster = " << i ;
		for (ll j = 0; j < VOCAB; ++j)
		{
			means[i][j]=0;
		}

		clustercount=0;

		for (ll j = 0; j < DOCS; ++j)
		{
			if(clusterid[j] == i){
				for (ll k = 0; k < VOCAB; ++k)
				{
					means[i][k] += data[j][k];
				}
				clustercount++;
			}
		}

		for (ll k = 0; k < VOCAB; ++k)
		{
			means[i][k] = (means[i][k]*1.0)/(clustercount);
		}
// if (epoch == 0 && i == 0){
// 	show_array(means[0], VOCAB);
// 	cout << "clustercount = " << clustercount << endl;
// }


	}

	cout << endl;
}

void getClusters(ll epoch){
	ll min_dist;
	ll d;
	for (ll i = 0; i < DOCS; ++i)
	{	
		cout << "\r" << "doc = " << i ;
		min_dist = LLONG_MAX;
		for (ll j = 0; j < n_clusters; ++j)
		{	
			d  = compute_distance(i, j);
			if(min_dist > d){
				clusterid[i] = j;
				min_dist = d;
			}
		}
		// cout << "compute dist i = " << i << ";cluster id = " <<clusterid[i] << endl;
		if(min_dist > LAMBDA){
			n_clusters++;
			// cout << "NEW = " << n_clusters << "i = "<< i << " " << clusterid[i] << endl;
			// show_array(data[0], VOCAB);
			// cout << "--------" << endl;
			// show_array(means[0], VOCAB);
			clusterid[i] = n_clusters-1;
			// cout << clusterid[i] << endl;
			ll* _mean = (ll*)malloc(VOCAB*sizeof(ll));
			for (ll k = 0; k < VOCAB; ++k)
			{
				_mean[i] = data[i][k];
			}
			means.pb(_mean);
		}

	}
	cout << endl;
}


int main(){
	readinput();

	for (int i = 0; i < EPOCHS; ++i)
	{
		cout << "epoch = " << i << endl;
		getClusters(i);
		updateMeans(i);
		
	}
	cout << "#Clusters " << n_clusters << "\n";

	// for(ll i=0; i< DOCS; i++){
	// 	cout << clusterid[i] << endl;
	// }
	cout << "program complete" << endl;

	return 0;
}