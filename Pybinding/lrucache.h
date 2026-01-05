#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <optional>
#include <functional>
#include "matrix.h"

struct LUResult {
    Matrix<double> lmat;
    Matrix<double> umat;
};

class LRUMatrixCache {
private:
    int capacity;
    std::list<std::pair<int, LUResult>> cacheList;
    std::unordered_map<int, std::list<std::pair<int, LUResult>>::iterator> cacheMap;

    void moveToFront(int key);

public:
    LRUMatrixCache(int cap);
    std::optional<LUResult> get(int key);
    void put(int key, const LUResult& value);
};

int hashMatrix(const Matrix<double>& A);
LUResult computeLU(const Matrix<double>& A);

#endif

