#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sys/time.h>
 timeval t1, t2;
     double elapsedTime;

using namespace std;
char chrs [] = 
{
    '0','1','2','3','4','5','6','7','8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Z',
    '_','-'
};
vector <char> chars (chrs, chrs + sizeof(chrs)/ sizeof(chrs[0]));

map<int, int> lookup;

char maxchar='-';
string uuid="0";
void fillLookup()
{
    for(int i=0; i<chars.size(); i++)
    {
        lookup[chars[i]]=i;
    }
}

void increase(int r)
{
    if(r<0)
    {
        uuid="0"+uuid;
        r=0;
        return; 
    }
    if(uuid[r]==maxchar)
    {
        uuid[r]='0';
        increase(r-1);
    }
    else
    {
        int next=(lookup[uuid[r]]+1)%chars.size();
        uuid[r]=chrs[next];
    }
}
int main ()
{
       gettimeofday(&t1, NULL);
    cout << "Alphabet size: "<< chars.size() << endl;
    fillLookup();
    int counter=0;
    int prev_status=0,status=-1;
    for(int i=0; 1; i++)
    {
           gettimeofday(&t2, NULL);
        increase(uuid.length()-1);
        //cout << uuid<<endl;
        if(uuid.length()==6)
            break;
        counter++;
        prev_status=status;
        status=(int)(100* (double)counter/992436543.0+ .5);
        if(prev_status!=status)
        {
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
            
            cout << "\r" << static_cast<int>( (double)counter/(elapsedTime/1000.0) + .5 ) << " urls/sec "<< status << "%";

            cout << flush;
        }
    }
}


