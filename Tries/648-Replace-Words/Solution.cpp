class Solution {
private:
    class Trie {
        private:
            bool isEnd;
            Trie *children[26];
        public:
            Trie(){
                isEnd = false;
                for( int i = 0; i < 26; i++ )
                    children[i] = NULL;
            }
        
            void insert( string s ){
                Trie *trie = this;
                for( char c : s ){
                    int idx = c - 'a';
                    if( trie->children[idx] == NULL )
                        trie->children[idx] = new Trie();
                    trie = trie->children[idx];
                }
                
                trie->isEnd = true;
            }
        
            string replace( string s ){
                
                Trie *trie = this;
                for( int i = 0; i < s.size(); i++ ){
                    int idx = s[i] - 'a';
                    if( trie->children[idx] == NULL )
                        return s;
                    trie = trie->children[idx];
                    
                    if( trie->isEnd ) {
                        return s.substr(0,i+1);
                    }
                }
                
                return s;
            }
    };
public:
    vector<string> parse( string s ){
        vector<string> result;
        
        int pos = s.find_first_of(" ");
        while( pos != string::npos ){
            result.push_back( s.substr(0,pos) );
            s = s.substr(pos+1);
            pos = s.find_first_of(" ");
        }
        
        if( s.size() > 0 ) 
            result.push_back(s);
        
        return result;
    }
    
    string replaceWords(vector<string>& dict, string sentence) {
        Trie * trie = new Trie();
        for( string s : dict ) trie->insert(s);
        
        vector<string> words = parse(sentence);
        stringstream buf;
                
        for( int i = 0; i < words.size(); i++ ){
            buf << trie->replace( words[i] );
            
            if( i + 1 != words.size() ) buf << " ";
        }
        
        
        return buf.str();
    }
};