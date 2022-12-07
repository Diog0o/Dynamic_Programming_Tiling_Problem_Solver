#include<vector>
#include<iostream>
#include<tuple>
#include<algorithm>
#include<iterator>
#include<unordered_map>

using namespace std;

unordered_map <string,int> cache;

vector<vector<int>> createMatrix (vector<int> dados);
vector<int> findCorner(vector<vector<int>> matrix);
vector<vector<int>> createBoundaries(vector<vector<int>> matrix);
bool canAddMatrix2x2 (vector<vector<int>> matrix);
vector<string> createPath (vector<vector<int>> matrix);


int main (){

    vector<vector<int>> vec = {{1,0,0},{1,1,0},{1,1,0}};

    

    createBoundaries(vec);

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
    // findNumberofTiles(dados);

    return 0;
}



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
    for (int k=0; k<dados[0]; k++){
        int counter = 2;
        for (int l=0; l<dados[counter];l++){
            counter++;
            res[k][l]=1;
        }
    }
    return res;
}
//add + 1 no i e no j 
vector<int> findCorner(vector<vector<int>> matrix){ //sq falta ver quando e 0
    vector<int> res;
    for (unsigned int i=0; i<matrix.size();i++ ){
        for (unsigned int j= matrix[0].size(); j>0;j--){
            if (matrix[i][j]==1){
                res.push_back(i);
                res.push_back(j);
                return res;
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

    for (unsigned int i=1; i<matrix.size()+1; i++){
        matrix_boundaries[i].push_back(0);
    }
    for (unsigned int i=0; i<matrix[0].size(); i++){
        lastline.push_back(1);
    }
    lastline.push_back(1);
    
    firstline.insert(firstline.begin(), 1);
    matrix_boundaries.push_back(lastline);
    matrix_boundaries.insert(matrix_boundaries.begin(), lastline);

    return matrix_boundaries;
}


vector<string> createPath (vector<vector<int>> matrix){
    unsigned int first_line = 1;
    unsigned int first_col = 1;
    
    vector<vector<int>> matrix_with_boundaries;
    matrix_with_boundaries= createBoundaries(matrix);
    vector<string> path;
    
    while ( first_line != matrix_with_boundaries.size()-1 && first_col != matrix_with_boundaries[0].size()-1){
        if(matrix_with_boundaries[first_line][first_col]==1 && matrix_with_boundaries[first_line-1][first_col]==0 ){
            path.push_back("H");
            first_col ++ ;
        }
        if(matrix_with_boundaries[first_line][first_col]==0){
            path.push_back("D");
            first_line++;
        }
        if (matrix_with_boundaries[first_line][first_col]==1 && matrix_with_boundaries[first_line-1][first_col]==1){
            path.push_back("U");
            first_line--;
       }
    }
    return path;
}

// vector<vector<int>> eliminate_square(vector<vector<int>> matrix, int size){ 
    
// }
















/*
Criar uma funcao que passe o input para uma lista de ints que consigamos usar depois

Pegar nessa info do input e criar uma matrix que tenha 1's nas posiçoes em que diz que tao preenchidas

Temos que criar uma funcao que diz se é possível ou nao adicionar um bloco de determinada dimensao

Temos que fazer uma funcao que pegue na matriz que tamos a analisar (no inicio vai ser aquela
que só tem 1's e vamos adicionar o bloco que queremos nas varias posições possiveis)

Isto vai se fazer para todas as opcoes possiveis, para que no final consigamos ver o tamanho da lista
e saber quantas opçoes possiveis é que existem.



*/

// vector<int> find_first_1(vector<vector<int>> matrix){
//     bool found = false;
//     vector<vector<int>> matrix_with_boundaries;
//     vector<int> res;
//     matrix_with_boundaries = createBoundaries(matrix);
//     for (unsigned int k=1; k< matrix_with_boundaries[0].size()-1; k++){ //runs the column
//         for (unsigned int l =1; l<matrix_with_boundaries.size()-1; l++){ //runs the line
//             if (matrix_with_boundaries[l][k] == 1 && found == false){
//                 res.push_back(l);
//                 res.push_back(k);
//                 found = true;
//             }
//         }
//     }
//     return res;

// }

// vector<int> find_last_1(vector<vector<int>> matrix){
  
//     bool found = false;
//     vector<vector<int>> matrix_with_boundaries;
//     vector<int> res;
//     matrix_with_boundaries = createBoundaries(matrix);
//     for (int o =matrix_with_boundaries[0].size(); o>1; o--){
//         for (int p = matrix_with_boundaries.size(); p>1; p--){
//             if (matrix_with_boundaries[p][o] == 1 && found == false){
//                 res.push_back(p);
//                 res.push_back(o);
//                 found = true;
//             }
//         }
//     }
//     return res;

// }

// bool canAddMatrix2x2 (vector<vector<int>> matrix){
//     vector<vector<int>> matrix_with_boundaries;
//     matrix_with_boundaries = createBoundaries(matrix);
//     for (unsigned int i = 1; i<matrix.size() +1; i++){
//         for (unsigned int j = 1; j<matrix[0].size() +1; j++){
//             if (matrix_with_boundaries[i][j] ==1){
//                 if (matrix_with_boundaries[i][j+1] == 1 && matrix_with_boundaries[i+1][j+1] == 1 \
//                 && matrix_with_boundaries[i+1][j] == 1){
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }