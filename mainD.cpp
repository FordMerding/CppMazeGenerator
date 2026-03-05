#include<bits/stdc++.h>
#define pb push_back
using namespace std;

bool used[10000];

int width = 20, height = 20;

set<int> vec[10000];
// u l d r
string walls[2][2][2][2] = {{{{"╬", "╣"}, {"╩", "╝"}}, {{"╠", "║"}, {"╚", "╨"}}}, {{{"╦", "╗"}, {"═", "╡"}}, {{"╔", "╥"}, {"╞", "▫"}}}};

void dfs(int v){
    used[v] = 1;
    int dir[4] = {1, 2, 3, 4};
    random_shuffle(dir, dir+4);
    for(auto x: dir){
        if(x == 1 && !used[v-width] && v-width > -1){
            vec[v-width].insert(v);
            dfs(v-width);
        }
        else if(x == 2 && !used[v+1] && v+1 < (v/width+1)*width){
            vec[v].insert(v+1);
            dfs(v+1);
        }
        else if(x == 3 && !used[v+width] && v + width < width * height){
            vec[v].insert(v+width);
            dfs(v+width);
        }
        else if(x == 4 && !used[v-1] && v-1 >= (v/width)*width && v-1 > 0){
            vec[v-1].insert(v);
            dfs(v-1);
        }
    }
}

void do_maze(){
    for(int i = 0; i < width * height; i++){
        used[i] = 0;
        vec[i].clear();
    }
    dfs(0);
}

void write_line(){
    cout<<"╔";
    for(int i = 0; i < width-1; i++){
        cout<<"═";
        if(vec[i].count(i+1))
        cout<<"═";
        else
        cout<<"╦";
    }
    cout<<"═╗";
    cout<<"\n";
}

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    // srand(42);
    do_maze();
    write_line();
    for(int i = 0; i < height; i++){
        cout<<"║";
        for(int j = 0; j < width; j++){
            cout<<" ";
            if(j == width - 1)
            cout<<"║";
            else{    
                if(vec[i*width + j].count(i*width + j + 1)){
                    cout<<" ";
                }
                else cout<<"║";
            }
        }
        cout<<"\n";
        
        if(i == height-1){
            cout<<"╚";
        }
        else if(vec[i*width].count(i*width+width))
            cout<<"║";
        else
            cout<<"╠";
        
        for(int j = 0; j < width; j++){
            if(vec[i*width+j].count(i*width+j+width)){
                cout<<" ";
            }
            else{
                cout<<"═";
            }

            bool down = 0, up = 0, left = 0, right = 0;
            left = vec[i*width+j].count((i+1)*width+j);
            if(j+1 < width){
                right = vec[i*width+j+1].count((i+1)*width+j+1);
                down = vec[(i+1)*width+j].count((i+1)*width+j+1);
                up = vec[i*width+j].count(i*width+j+1);
            }
            else{
                right = 1;
            }

            if(i == height -1){
                down = 1;
            }
            cout<<walls[up][left][down][right];
        }
        cout<<"\n";
    }
}
