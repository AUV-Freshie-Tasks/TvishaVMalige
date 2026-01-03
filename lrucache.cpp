#include "lrucache.h"

/* LRU Cache */
LRUMatrixCache::LRUMatrixCache(int cap) : capacity(cap) {}

void LRUMatrixCache::moveToFront(int key) {
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
}

std::optional<LUResult> LRUMatrixCache::get(int key) {
    if (cacheMap.find(key) == cacheMap.end())
        return std::nullopt;
    moveToFront(key);
    return cacheMap[key]->second;
}

void LRUMatrixCache::put(int key, const LUResult& value) {
    if (cacheMap.find(key) != cacheMap.end()) {
        moveToFront(key);
        cacheMap[key]->second = value;
        return;
    }

    if (cacheList.size() == capacity) {
        cacheMap.erase(cacheList.back().first);
        cacheList.pop_back();
    }

    cacheList.emplace_front(key, value);
    cacheMap[key] = cacheList.begin();
}

/* Hash */
int hashMatrix(const Matrix<double>& A) {
    long long h = 0;
    for (int i = 0; i < A.Rows(); i++) {
        for (int j = 0; j < A.Columns(); j++) {
            // Round to avoid floating point precision differences
            int val = static_cast<int>(A(i,j) * 100000); 
            h = h * 131 + val;
        }
    }
    return static_cast<int>(h);
}

/* LU Decomposition with Cache */
LUResult computeLU(const Matrix<double>& A) {
    static LRUMatrixCache luCache(10);

    int key = hashMatrix(A);
    auto cached = luCache.get(key);
    if (cached.has_value()) {
	    cout << "Cache HIT" << endl;
	    return cached.value();
    }
	
    cout << "Cache MISS. Computing LU" << endl;
    int n = A.Rows();
    Matrix<double> L = Matrix<double>::identity(n);
    Matrix<double> U(n, n);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += L(i, k) * U(k, j);
            U(i, j) = A(i, j) - sum;
        }

        for (int i = j + 1; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < j; k++)
                sum += L(i, k) * U(k, j);
            L(i, j) = (A(i, j) - sum) / U(j, j);
        }
    }
	







    LUResult result{L, U};
    luCache.put(key, result);
    return result;
}

