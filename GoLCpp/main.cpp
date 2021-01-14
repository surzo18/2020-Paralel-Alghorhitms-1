#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <thread>

using namespace std::chrono_literals;

void print(std::vector<std::vector<int>> &arr){
    for (int col = 0; col < arr[0].size(); ++col) {
        std::cout << "---";
    }
    std::cout << "--" << std::endl;

    for (int i = 0; i < arr.size(); ++i) {
        std::cout<< "|";
        for (int j = 0; j < arr[0].size(); ++j) {
            if (arr[i][j]==1){
//                std::cout<<" "<<arr[i][j]<<" ";//<<" ■ ";
                std::cout<<" ■ ";
            }
            else{
//                std::cout<<" "<<arr[i][j]<<" ";//<<"   ";       //□  ⬜
                std::cout<<"   ";

            }
        }
        std::cout<< "|" <<std::endl;
    }
    for (int col = 0; col < arr[0].size(); ++col) {
        std::cout << "---";
    }
    std::cout << "--" << std::endl;

}

void surroundings(int &i, int &j, std::vector<std::vector<int>> &arr, int &counter) {
	for (int k = i - 1; k < i + 2; ++k) {
	    for (int l = j - 1; l < j + 2; ++l) {
            if (k >= 0 &&
                l >= 0 &&
                k < arr.size() &&
                l < arr[0].size() &&
                (!(k == i && l == j))) { //medze
                    if (arr[k][l] == 1) {    //susedia
                        ++counter;
                    }
                }
	    }
	}
}
void lineInThread(std::vector<std::vector<int>> &arr, std::vector<int> &result, int line) {
    int counter = 0;
    std::vector<int> tmpLine;
//    tmpLine.resize(arr.size());

    for (int cell = 0; cell < arr[line].size(); ++cell) {
        counter = 0;
        surroundings(line, cell, arr, counter);
        if (arr[line][cell] && counter < 2)                             tmpLine.push_back(0);
        else if (arr[line][cell] && (counter == 2 || counter == 3))     tmpLine.push_back(1);
        else if (arr[line][cell] && counter > 3)                        tmpLine.push_back(0);
        else if (arr[line][cell]==0 && counter == 3)                    tmpLine.push_back(1);
        else                                                            tmpLine.push_back(0);
    }

    result = tmpLine;
}

void paralelRound(std::vector<std::vector<int>> &arr){
    std::vector<std::thread> threads;
    std::vector<std::vector<int>> tmp;
    threads.reserve(arr.size());
    tmp.resize(arr.size());
    for (int th = 0; th < arr.size(); ++th){
        threads.emplace_back(std::thread(lineInThread,std::ref(arr), std::ref(tmp[th]), th));
    }

    for (std::thread & th : threads){
        if (th.joinable())
            th.join();
    }
    arr = tmp;
//    std::cout<<std::endl;
}

void round(std::vector<std::vector<int>> &arr){
    std::vector<std::vector<int>> tmp;
    tmp.resize(arr.size());
    for (int i = 0; i < arr.size(); ++i) {
        tmp[i].resize(arr[i].size());
    }

    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr[i].size(); ++j) {
            int counter = 0;
	        surroundings(i, j, arr, counter);
//	  	std::cout<< counter<<std::endl;
            if (arr[i][j] && counter<2 ){                                   //otocene znamienko >
                tmp[i][j]= 0;
            }
            else if (arr[i][j] && (counter == 2 || counter == 3 )){
                tmp[i][j]= 1;
            }
            else if (arr[i][j] && counter >3){
                tmp[i][j]= 0;
            }
            else if (!arr[i][j] && counter==3 ){
                tmp[i][j]= 1;
            }

//            else std::cout << "kurwa (with flowers) "<<counter << " "<<tmp[i][j] <<std::endl;
        }
    }
    arr=tmp;
}


int main() {
//    std::vector<std::vector<int>> playingBoard= {{0, 0, 0, 0, 0, 0},
//                                                 {0, 0, 0, 1, 0, 0},
//                                                 {0, 1, 0, 0, 1, 0},
//                                                 {0, 1, 0, 0, 1, 0},
//                                                 {0, 0, 1, 0, 0, 0},
//                                                 {0, 0, 0, 0, 0, 0}};
//    std::vector<std::vector<int>> playingBoard= {{1, 1},
//                                                 {1, 0}};

std::vector<std::vector<int>> playingBoard= {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

    print(playingBoard);
    while (true){
        paralelRound(playingBoard);
    #if defined(_WIN_32)
            system("cls")
    #endif
    #if defined(linux)
        std::cout << "\033[2J\033[1;1H";
    #endif
        print(playingBoard);
        std::this_thread::sleep_for(100ms);
    }

    return 0;
}
