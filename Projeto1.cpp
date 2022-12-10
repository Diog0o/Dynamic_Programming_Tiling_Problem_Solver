#include<vector>
#include<iostream>
#include<tuple>
#include<algorithm>
#include<iterator>
#include<unordered_map>
#include <utility>
#include <string>


using namespace std;

unordered_map <string,int> cache;


vector<vector<int>> createMatrix (vector<int> dados);
vector<int> findCorner(vector<vector<int>> matrix);
vector<vector<int>> createBoundaries(vector<vector<int>> matrix);
bool canAddMatrix2x2 (vector<vector<int>> matrix);
string createPath (vector<vector<int>> matrix);




vector<vector<int>> createMatrix (vector<int> dados){
    // dados[0]=n == linhas; dados[1]=m == colunas ;;; matriz nxm ;
    vector<vector<int>> res;
    for (int i =0; i<dados[0];i++){
        vector<int> linhas = {};
        for (int j=0; j<dados[1]; j++){
            linhas.push_back(0);
        }
        res.push_back(linhas);
    }
    int counter = 2;
    for (int k=0; k<dados[0]; k++){
        for (int l=0; l<dados[counter];l++){
            res[k][l]=1;
        }
        counter++;
    }
    return res;
}

vector<int> findCorner(vector<vector<int>> matrix){ //sq falta ver quando e 0
    vector<int> res;
    for ( int i=0; i<= matrix.size()-1;i++ ){
        for ( int j= matrix[0].size()-1; j>=0 ;j--){
            if (j < matrix[0].size()){
                if (matrix[i][j]==1){
                    res.push_back(i);
                    res.push_back(j);
                    return res;
                }
            }
        }
    }
    return res;
}

vector<vector<int>> createBoundaries(vector<vector<int>> matrix){ //meter 1's em baixo
    vector<int> firstline;
    vector <int> lastline;
    vector<vector<int>> matrix_boundaries;
    copy(matrix.begin(), matrix.end(), back_inserter(matrix_boundaries)); 
    
    for (unsigned int i=0; i<matrix[0].size()+1 ; i++){
        firstline.push_back(0);
    }

    for (unsigned int i=0; i<matrix.size()+1; i++){
        matrix_boundaries[i].push_back(0);
    }
    for (unsigned int i=0; i<matrix[0].size(); i++){
        lastline.push_back(1);
    }
    lastline.push_back(0);
    
    matrix_boundaries.push_back(lastline);
    matrix_boundaries.insert(matrix_boundaries.begin(), firstline);

    return matrix_boundaries;
}


string createPath (vector<vector<int>> matrix){
    unsigned int first_line = 1;
    unsigned int first_col = 0;
    
    vector<vector<int>> matrix_with_boundaries = createBoundaries(matrix);
    string path;
    
    while ( first_line != matrix_with_boundaries.size()-1 || first_col != matrix_with_boundaries[0].size()-1){
        if(matrix_with_boundaries[first_line][first_col]==1 && matrix_with_boundaries[first_line-1][first_col]==0 ){
            path += "H";
            first_col ++ ;
        }
        if(matrix_with_boundaries[first_line][first_col]==0){
            path += "D";
            first_line++;
        }
        if (matrix_with_boundaries[first_line][first_col]==1 && matrix_with_boundaries[first_line-1][first_col]==1){
            path += "U";
            first_line--;
       }
    }
    return path;
}

vector<vector<int>> eliminate_square(vector<vector<int>> matrix, int size){ //quando usarmos temos que garantir que nao sai da matriz
    vector<vector<int>> matrix_mudada;
    copy(matrix.begin(), matrix.end(), back_inserter(matrix_mudada));
    vector<int> corner = findCorner(matrix);
    int i = corner[0];
    int j = corner[1];
    int stop1 = i+size;
    int stop2 = j-size;
    for(int i = corner[0]; i< stop1 ; i++){
        for (int j = corner[1]; j> stop2 ; j--){
            matrix_mudada[i][j]=0;     
        }
    }
    return matrix_mudada;
}


bool isPossible (vector<vector<int>> matrix, int size){
    vector<int> corner = findCorner(matrix);
    int i = matrix.size() - corner[0] +1;
    int j = corner[1] +1;
    if (i-size < 0 || j-size<0){
        return false;
    }
    int k = corner[0];
    int l = corner[1];
    int stop1 = k+size-1;
    int stop2 = l+1-size;
    for(int k = corner[0]; k<= stop1 ; k++){
        for (int l = corner[1]; l>= stop2 ; l--){
            if(matrix[k][l]==0){
                return false;
            }
        }
    }
    return true;
}



int contafig ( vector<vector<int>> matrix){
    vector<vector<int>> c;
    copy(matrix.begin(), matrix.end(), back_inserter(c)); 
    vector<vector<int>> c_;
    int maxi = max(matrix.size() , matrix[0].size());
    int r =0;
    for(int i =1 ; i<maxi; i++){
        if (isPossible(c, i) == true){
            c_ = eliminate_square(c,i);
            string path = createPath(c_);

            auto iter = cache.find(path);
            if (iter != cache.end()) {
                r += cache[path];
            }else{
                pair<string,int> pair_of_values (path,r);
                cache.insert(pair_of_values);
            }
            copy(c_.begin(), c_.end(), back_inserter(c));
            r += contafig(c_);
        }
    }
    return r;
}

void mostra_vector (vector<vector<int>> matrix){
    for (unsigned int i =0; i< matrix.size();i++){
        printf("%s", "\n");
        for (unsigned int j=0; j<matrix[0].size(); j++){
            printf("%d",matrix[i][j]);
        }
    }
}

void mostra_vector_int (vector<int> veca){
    printf("%s", "\n");
    for (unsigned int i=0; i<veca.size(); i++){
        printf("%d", veca[i]);
    }
}

void mostra_string (string path){
    printf("%s", path);
}

int main (){

    vector<vector<int>> vec = {{1,1,1},{1,1,1},{1,1,1}};
    vector<int> dados;
    dados.push_back(3);
    dados.push_back(3);
    dados.push_back(3);
    dados.push_back(3);
    dados.push_back(3);
    
    //mostra_vector(createMatrix(dados));
    //mostra_vector(createMatrix(dados));
    //mostra_vector_int(findCorner(vec));
    //mostra_vector(createBoundaries(vec));
    //mostra_string(createPath(vec));
    //mostra_vector(eliminate_square(vec, 1));

    cout << contafig(vec);

    // vector<int> dados ;

    // int n;
    // scanf("%d", &n);
    // dados.push_back(n);

    // int m;
    // scanf("%d", &m);
    // dados.push_back(m);

    // int counter=0;
    // while (counter != n){
    //     int f;
    //     scanf("%d", &f);
    //     dados.push_back(f);
    //     counter++;
    // }
    //contafig(dados);

    return 0;
}
