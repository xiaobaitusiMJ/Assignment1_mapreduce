#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<string>//getline������string��������
#include <sstream>  

using namespace std;

struct wordPair{string keyWord; int num;};


void tMap(string,vector<wordPair> *words);
void tCombine(vector<wordPair> *words1,vector<wordPair> *words2);

int main()
{
        vector<wordPair> VecWords1;
        vector<wordPair> VecWords2;
        fstream f("D:\\projects\\MapReduce\\MapReduce\\input.txt");
        std::string _line;
        std::string _word;
        

        while(getline(f,_line))
        {
                tMap(_line,&VecWords1);
                cout<<endl;
                tCombine(&VecWords1,&VecWords2);
                vector<wordPair>::iterator iter = VecWords2.begin();
                while(iter!=VecWords2.end())
                {
                        cout<<iter->keyWord<<','<<iter->num<<' ';
                        iter++;
                }
                cout<<endl;
                cout<<endl;
                VecWords1.clear();
                VecWords2.clear();
                
        }
        delete &VecWords1;
        delete &VecWords2;
        system("pause");
        return 0;

}


void tMap(string myLine,vector<wordPair> *pVecWords)
{
        string myWord;
        wordPair _wordPair;
        string separators(" \t:,\v\r\n\f");//����������������
        string::size_type startPos=0,endPos=0;//��������������������
        string::size_type maxLen,minLen,wordLen,count=0;//sentence��������������������������������������������
        
        endPos=myLine.find_first_of(separators,endPos);//������������������
        
        if(endPos == string::npos)//��������������������������������������������
                wordLen = myLine.size() - startPos;
        else
                wordLen = endPos-startPos;
        myWord.assign(myLine.begin()+startPos,myLine.begin()+startPos+wordLen);//��������
        cout<<myWord<<' ';
        _wordPair.keyWord = myWord;
        _wordPair.num = 1;
        pVecWords->push_back(_wordPair);
        startPos = myLine.find_first_not_of(separators,endPos);//����������������������
        
        while((startPos=myLine.find_first_of(separators,endPos))!=string::npos)//��������������������
        {
                startPos++;
                endPos = myLine.find_first_of(separators,startPos);//����������������������

                if((endPos-startPos)==0)//��������������������������������
                        ;//nothing
                else
                {

                
                        if(endPos == string::npos)//����������������������������������������������
                                wordLen = myLine.size() - startPos;
                        else
                                wordLen = endPos-startPos;

                        myWord.assign(myLine.begin()+startPos,myLine.begin()+startPos+wordLen);//��������
                        cout<<myWord<<' ';
                        _wordPair.keyWord = myWord;
                        _wordPair.num = 1;
                        pVecWords->push_back(_wordPair);
                        startPos = myLine.find_first_not_of(separators,endPos);//����������������������         
                }
        }

        cout<<endl;

        
}

void tCombine(vector<wordPair> *words1,vector<wordPair> *words2)
{
        //vector<wordPair> words1;
        vector<wordPair>::iterator iter1 = words1->begin();
        vector<wordPair>::iterator iter2;
        int cnt1=0;
        int     cnt2=0;
        //wordPair tmpPair;
        //bool alreadyInVec = false;

        while(iter1!=words1->end())
        {
                iter2 = words2->begin();
                while(iter2!=words2->end())
                {
                        if (iter1->keyWord.compare(iter2->keyWord)==0)
                        {
                                iter2->num += iter1->num;
                                break;
                        }
                        
                        iter2++;
                }
                if (iter2==words2->end())//not exist in the vec
                {
                        words2->push_back(*iter1);
                }
                iter1++;


        }

        
}
