/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int intValue(string s, int startIndex, int endIndex) {
        int returnVal = 0;
        int multiplier = 1;
        if(s[startIndex] == '-') {
            multiplier = -1;
            startIndex++;
        }
        for(int i = startIndex; i <= endIndex; i++) {
            returnVal *= 10;
            returnVal += s[i] - '0';
        }
        return returnVal*multiplier;
    }
    NestedInteger deserialize(string s) {
        // Corner cases "", "123"
        if(s.length() == 0) return NestedInteger();
        if(s[0] != '[') return NestedInteger(intValue(s,0,s.length()-1));
        
        // Cases of the form "[...]" - internal should handle them
        return deserializeInternal(s,0,s.length()-1);
    }
    
    NestedInteger deserializeInternal(string s, int startIndex, int endIndex) { // Handle cases of the form "[]", "[...[...]...]"
        NestedInteger outerNode;
        string currString = "";
        for(int i = startIndex+1; i < endIndex; i++) {
            if(s[i] == '[') { // Advance till matching close parenthesis 
                int internalStart = i;
                i++;
                int open = 1;
                while(open > 0) {
                    if(s[i] == '[') open++;
                    else if(s[i] == ']') open--;
                    i++;
                }
                int internalClose = i-1;
                outerNode.add(deserializeInternal(s,internalStart,internalClose));
                currString = "";
            }
            else if(s[i] == ',') {
                outerNode.add(NestedInteger(intValue(currString,0,currString.length()-1)));
                currString = "";
            }
            else currString += s[i];
        }
        if(currString.length() > 0) {
            outerNode.add(NestedInteger(intValue(currString,0,currString.length()-1)));
            currString = "";
        }
        return outerNode;
    }
};