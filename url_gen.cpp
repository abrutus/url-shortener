#include <kcpolydb.h>
using namespace std;
using namespace kyotocabinet;

class UrlGenerator
{
        HashDB db;
        map<int, int> lookup;
        vector <char> chars;
        string current_str;
        int r;
        void fillLookup()
        {
            for(int i=0; i<chars.size(); i++)
            {
                lookup[chars[i]]=i;
            }
        }
        string increase() { return increase(current_str.length()-1); } 
        string increase(int r)
        {
            if(r<0)
            {
                current_str="0"+current_str;
                r=0;
            }
            else if(current_str[r]=='-')
            {
                current_str[r]='0';
                increase(r-1);
            }
            else
            {
                int next=(lookup[current_str[r]]+1)%chars.size();
               cout << next;
                current_str[r]=chars[next];
            }
            db.set("current_str", current_str);
        }
    public:
        UrlGenerator() : current_str("0"), r(0)
        {
            char chrs [] = 
            {
                '0','1','2','3','4','5','6','7','8','9',
                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Z',
                '_','-'
            };
            vector <char> charx (chrs, chrs + sizeof(chrs)/ sizeof(chrs[0]));
            chars=charx;
            fillLookup();
            
            // open the database
            if (!db.open("casket.kch", HashDB::OWRITER | HashDB::OCREATE)) {
                cerr << "open error: " << db.error().name() << endl;
            }
            // retrieve last_url
            if (db.get("current_str", &current_str)) {
                cout << "Last Url:" << current_str << endl;
            } else {
                cout << "No last url, resetting to 0" << endl;
                db.set("current_str", "0");
                current_str="0";
            }
        }
        ~UrlGenerator()
        {
            if (!db.close()) {
                cerr << "close error: " << db.error().name() << endl;
            }
        }
        bool next(string url)
        {
        cout << increase(current_str.length()-1);  
            return 1; //return db.set(increase(), udrl);
        }

};
