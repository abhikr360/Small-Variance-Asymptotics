#include<iostream>
#include <vector>
#include<cstdlib>
#include<climits>
using namespace std;


#define pb push_back
#define ll long long int



#define N_DATASETS 8
#define EPOCHS 10
#define VOCAB 53975
#define LAMBDA_L 10000
#define LAMBDA_G 10000



ll ***data;
ll* clusterid;
vector<ll*> global_means;
vector<ll> local_to_global[N_DATASETS];
ll n_global_clusters;
ll n_local_clusters[N_DATASETS];
ll n_points[N_DATASETS];
ll* Z[N_DATASETS]
vector<ll>  V[N_DATASETS]




void show_array(ll* arr, ll size){
	for (ll i=0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
	return;
}

ll compute_distance(ll dataset_id, ll docid, ll global_clusterid){
	ll d =0;
	ll temp;

	for (ll i = 0; i < VOCAB; ++i)
	{
		temp = (data[dataset_id][docid][i]- global_means[global_clusterid][i]);
		d += temp*temp;
		if(d > LLONG_MAX - 1000){
			cout << "d may exceed the limit .............................................. " << docid << " " <<  clusterid << "\n";
			exit(1);
		}
	}
	return d;
}

ll findmin(ll* a, ll size){
	ll min_idx=0;
	ll min = LLONG_MAX;
	ll t;
	for (int i = 0; i < size; ++i)
	{	
		t=a[i];
		if( t < min){
			min_idx = i;
			min = t;
		}
	}
	return min_idx;
}

void copyarray(ll* a1 , ll* a2, ll size){
	for (int i = 0; i < size; ++i)
	{
		a1[i]=a2[i];
	}
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

	//Set \mu_1
	/////////////////////////////////////////////////////
	n_global_clusters=1;
	for (int i = 0; i < N_DATASETS; ++i)
	{
		n_local_clusters[i]=1;
		V[i].pb(0)
	}
	for (ll i = 0; i < N_DATASETS; ++i)
	{
		Z[i] = (ll*)malloc(n_points[i]*sizeof(ll))
		for (ll j=0; j < n_points; ++j)
		{
			Z[i][j]=0;
		}
	}
}



void getClusters(){
	int flag;
	ll* temp = (ll*) malloc(n_global_clusters*sizeof(ll));
	for (ll i = 0; i < N_DATASETS; ++i)
	{
		for (ll j = 0; j < n_points[i]; ++j)
		{
			for (ll p = 0; p < n_global_clusters; ++p)
			{
				temp[p]=compute_distance(i, j, p);
				flag=1;
				for (ll c = 0; c < V[i].size(); ++c)
				{
					if(V[i][c] == p){
						flag=0;
						break;
					}
				}
				if(flag){
					temp[p] += LAMBDA_L;
				}

			}
			p_min = findmin(temp, n_global_clusters);
			if(temp[p_min] > LAMBDA_L + LAMBDA_G){
				n_local_clusters[i]++;
				Z[i][j]=n_local_clusters[i]-1;
				n_global_clusters++;
				V[i].pb(n_global_clusters-1);
				ll* newpt = (ll*)malloc(VOCAB*sizeof(ll));
				copyarray(newpt, data[i][j], VOCAB);
				global_means.pb(newpt);
			}
			else{
				flag=0;
				ll c;
				for (c = 0; c < V[i].size(); ++c)
				{
					if(V[i][c] == p_min){
						flag=1;
						break;
					}
				}
				if(flag){
					Z[i][j]=c;
				}
				else{
					n_local_clusters[i]++;
					Z[i][j]=n_local_clusters[i]-1;
					V[i].pb(p_min);
				}
			}
		}
	}

	free(temp);
}


void updateLocalClusters(){
	ll* djcp = (ll*) malloc(n_global_clusters*sizeof(ll))
	ll n=0;
	for (ll i = 0; i < N_DATASETS; ++i)
	{
		for (ll c = 0; c < n_local_clusters[i]; ++c)
		{
			ll* temp = (ll*) malloc(VOCAB*sizeof(ll));
			n=0;
			for (ll idx = 0; idx < VOCAB; ++idx)
			{
				temp[idx]=0;
			}
			for (ll j = 0; j < n_points[i]; ++j)
			{
				if(Z[i][j] == c){
					n++;
					for (ll idx = 0; idx < VOCAB; ++idx)
					{
						temp[idx] += data[i][j][idx];
					}
					for (ll p = 0; p < n_global_clusters; ++p)
					{
						djcp[p] += compute_distance(i, j, p)
					}
				}
			}
			for (ll idx = 0; idx < VOCAB; ++idx)
			{
				temp[idx] = (temp[idx]*1.0)/n;
			}

			ll p_min = findmin(djcp, n_global_clusters);
			ll clust_int_dist=0;
			for (ll j = 0; j < n_points[i]; ++j)
			{
				if(Z[i][j] == c){
					clust_int_dist += compute_distance_custom(data[i][j], temp, VOCAB);
				}
			}
			if(djcp[p_min] > LAMBDA_G + clust_int_dist){
				n_global_clusters++;
				V[i][c]=n_global_clusters-1;
				global_means.pb(temp);

			}
			else{
				V[i][c] = p_min;
			}

		}
	}

	free(djcp);
}



void updateGlobalClusters(){
	for (ll p = 0; p < n_global_clusters; ++p)
	{	
		ll n=0
		for (ll i = 0; i < N_DATASETS; ++i)
		{
			for (ll j = 0; j < count; ++j)
			{
				if(V[j][Z[i][j]] == p){
					n++;
					for (ll idx = 0; idx < VOCAB; ++idx)
					{
						global_means[p][idx] += data[i][j][idx];
					}
				}
			}
		}
		for (ll idx = 0; idx < VOCAB; ++idx)
		{
			global_means[p][idx] = (global_means[p][idx]*1.0)/n;
		}
	}
}


int main(){
	readinput();

	for (int i = 0; i < EPOCHS; ++i)
	{
		cout << "epoch = " << i << endl;
		getClusters();
		updateLocalClusters();
		updateGlobalClusters();
		
	}
	cout << "#Clusters " << n_clusters << "\n";

	// for(ll i=0; i< DOCS; i++){
	// 	cout << clusterid[i] << endl;
	// }
	cout << "program complete" << endl;

	return 0;
}