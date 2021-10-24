/*剑指offer*/
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> B(A.size(),1);
        int size = A.size();
        for(int i = 1; i < size; i++){
            B[0] = A[i] * B[0];
        }
        for(int i = 1; i < (size-1); i++){
            for(int j = 0; j < A.size(); j++){
                if(j == i){
                    j++;
                }
                B[i] = A[j] * B[i];
            }
        }
        for(int i = 0; i < (size-1); i++){
            B[size-1] = A[i] * B[size-1];
        }
        
        return B;
    }
};

class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> B(A.size(), 1);

        for(int i = 1; i < A.size(); i++){
            B[i] = B[i-1] * A[i-1];//左半部分
        }
        int temp = 1;
        for(int j = (A.size()-2); j >= 0; j--){
            temp *= A[j+1];//右半部分
            B[j] *= temp;
        }

        return B;
    }
};
