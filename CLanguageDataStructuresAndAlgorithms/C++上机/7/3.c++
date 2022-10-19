//从文件读取单词，每个单词一行，不超过40个字符，单词内部
//没有空格。
//请按照出现次数从高到低的原则依次输出这些单词
//及其出现次数。出现次数相同的，请将字典序靠前的优先输出
#include <iostream>    //cin、cout
#include <string>      //string
#include <stdio.h>     //freopen 也可以对C++中的输入重定向
#include <map>
#include <fstream>

using namespace std;


class Word                           //set保存自定义数据(一定要重载<,否则set无法排序)
{
private:
	int id;
	string content;
public:
	Word (int id, string content)
	{
		this->id = id;
		this->content = content;
	}
	void print() const
	{
		printf ("content = %s\n,id = %d, ", content.c_str(),id);
	}
	bool operator <( const Word& w) const
	{
		return (content[0] < w.content[0]);
		
	}

};

//遍历函数
void Traverse(map<string,int> w) {                           
	for(auto iter=w.begin();iter!=w.end();iter++){
        cout<< iter->first <<" "<< iter->second <<endl;
    }
    

}
//获取单词函数GetWords
void InsertWords(map<string,int>& w,string key){

    int tag=w.count(key);
    if(tag==0){
        //不存在则插入
        w.insert({key,1});

    }else{

        map<string, int>::iterator it = w.find(key);
		//countmap.end()是map中最后一个元素的下一个
		if (it != w.end())
		{
			//如果找到，value++；
			it->second++;
		}

       
    }

}
//从文件读取单词
int main(){
    char c[40];
    map<string,int> w;
    ifstream inFile("words.txt", ios::in | ios::binary);
    if (!inFile) {
        cout << "error" << endl;
        return 0;
    }

    //连续以行为单位，读取 words.txt 文件中的数据
    while (inFile.getline(c, 40)) {
        InsertWords(w,c);
    }
    Traverse(w);
    inFile.close();
    return 0;

}

