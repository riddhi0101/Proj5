#include "StringUtils.h"
#include <algorithm> 
#include <cctype>
#include <cstdio>

namespace StringUtils{

    std::string Slice(const std::string &str, ssize_t start, ssize_t end){
        std::string subString;
        int length = str.length();
        if (start >= length){
            subString = "";
        }else if (end ==0 or end >= length) {
            for (int i = start; i < length; ++i){
                subString.push_back(str[i]);
            }
        }
        else{
            int startp = 0;
            int endp = 0;
            if (start < 0){
                startp = length + start;
            }else{
                startp = start;
            }
            if (end < 0){
                endp = length + end;
            }else {
                endp = end;
            }
            for (int i = startp; i < endp; ++i) {
                subString.push_back(str[i]);
            }

        }
        return subString;
    }


    std::string Capitalize(const std::string &str){
        std::string subString;
        for (auto i : str){
            subString.push_back(tolower(i));
        }
        subString[0] = toupper(subString[0]);
        return subString;
    }

    std::string Title(const std::string &str){
        std::string subString;
        int length = str.length();
        for (auto i : str){
            subString.push_back(tolower(i));
        }
        for (int i = 0; i < length; ++i){
            if (not(isalpha(subString[i]))) {
                subString[i+1] = toupper(subString[i + 1]);
            }
        }
        subString[0] = toupper(subString[0]);
        return subString;
    }

    std::string LStrip(const std::string &str){
        std::string subString;
        int length = str.length();
        int i = 0;
        while (isspace(str[i])){
            ++i;
        }for (int j = i; j < length; ++j){
            subString.push_back(str[j]);
        }
        return subString;
    }

    std::string RStrip(const std::string &str){
        std::string subString;
        int i = str.length() - 1;
        while (isspace(str[i])){
            --i;
        }for (int j = 0; j <= i ; ++j){
            subString.push_back(str[j]);
        }
        return subString;
    }

    std::string Strip(const std::string &str){
        std::string subString;
        int start = 0;
        while (isspace(str[start])){
            ++start;}
        int end = str.length() - 1;
        while (isspace(str[end])){
            --end;}
        for (int i = start; i <= end ; ++i){
            subString.push_back(str[i]);
        }
        return subString;
    }

    std::string Center(const std::string &str, int width, char fill){
        std::string subString;
        int length = str.length();
        int front = (width - length)/2;
        int back = width - front -length;
        for (int i = 0;i < front; ++i){
            subString.push_back(fill);
        }
        for (int i = 0; i<length; ++i){
            subString.push_back(str[i]);
        }
        for (int j = 0; j<back; ++j){
            subString.push_back(fill);
        }
        return subString;

    }

    std::string LJust(const std::string &str, int width, char fill){
        std::string subString;
        int length = str.length();
        int back = width - length;
        for (int i = 0; i<length; ++i){
            subString.push_back(str[i]);
        }
        for (int i = 0;i < back; ++i){
            subString.push_back(fill);
        }
        return subString;
    }

    std::string RJust(const std::string &str, int width, char fill){
        std::string subString;
        int length = str.length();
        int front = width - length;
        for (int i = 0;i < front; ++i){
            subString.push_back(fill);
        }
        for (int i = 0; i<length; ++i){
            subString.push_back(str[i]);
        }
        return subString;
    }

    std::string Replace(const std::string &str, const std::string &old, const std::string &rep){
        std::string subString;
        ssize_t lengthstr = str.length();
        int lengthf = old.length();// why does it say that the length of "\\" is 1
        size_t lastfound = 0;
        size_t found = str.find(old);
        while(lastfound < lengthstr){
            subString.append(str,lastfound, (found - lastfound));
            subString.append(rep);
            lastfound = found + lengthf;
            found = str.find(old,lastfound);
            if (found == std::string::npos){
                subString.append(str,lastfound, (found - lastfound));
                break;
            }
        }
        return subString;
    }

    std::vector< std::string > Split(const std::string &str, const std::string &splt){//doesnt work for the tougher test
        std::vector< std::string > endlist;
        int length = str.length();
        std::size_t lastfound = 0;
        if (splt == ""){
            int i = 0;
            int foundx = 0;
            std::string substring;
            while (i < length){//waht to find the first space and keep track until i get to the last space and then add all alpha to substring
                while (str[i] != ' ' and str[i] != '\t' and str[i] != '\n' and i < (length)){
                    substring.push_back(str[i]);
                    i++;
                }
                if (substring != "") {
                    endlist.push_back(substring);
                }
                substring = "";
                i++;
            }
        }
        else{
            std::size_t found = str.find(splt);
            if (found==std::string::npos){
                endlist.push_back(str);
            }
            else{
                while(lastfound < length){
                    endlist.push_back(str.substr(lastfound,found - lastfound));
                    lastfound = found+1;
                    found = str.find(splt,lastfound);
                    if (found == std::string::npos){
                        endlist.push_back(str.substr(lastfound,found - lastfound));
                        break;}
                }
            }


        }

        return endlist;
    }


    std::string Join(const std::string &str, const std::vector< std::string > &vect){
        std::string subString;
        int numelements = vect.size();
        for (int i = 0; i < (numelements - 1); i++){
            subString.append(vect[i]);
            subString.append(str);
        }
        if (numelements != 0 ){
            subString.append(vect[numelements -1]);
        }
        return subString;
    }

//reference: https://stackoverflow.com/questions/34546171/python-expandtabs-string-operation
    std::string ExpandTabs(const std::string &str, int tabsize){
        int currentpos = 0;
        std::string newstring;
        for (auto i : str){
            if (i != '\t'){
                newstring.push_back(i);
                currentpos++;
            }else{
                if (tabsize == 0){
                    currentpos = 0;
                }else{
                    for (int j = 0; j<(tabsize-(currentpos % tabsize)); j++){
                        newstring.push_back(' ');
                    }
                    currentpos = 0;
                }
            }
        }
        return newstring;
    }

    //https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++(changes to incorporate ignorecase)
    int EditDistance(const std::string &left, const std::string &right, bool ignorecase){
        std:: string leftr;
        std:: string rightr;
        if (ignorecase == true){
            for (auto i : left){
                leftr.push_back(tolower(i));}
            for (auto i : right){
                rightr.push_back(tolower(i));}
        }
        else{
            for (auto i : left){
                leftr.push_back(i);}
            for (auto i : right){
                rightr.push_back(i);}
        }
        const std::size_t len1 = left.size(), len2 = right.size();
        std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

        d[0][0] = 0;
        for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
        for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

        for(unsigned int i = 1; i <= len1; ++i)
            for(unsigned int j = 1; j <= len2; ++j)
                d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (leftr[i - 1] == rightr[j - 1] ? 0 : 1) });
        return d[len1][len2];

    }

}