//ObjectPool.h
#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <vector>

#include "TFigure.h"

//----------------------------------------
class ObjectPool{
private:
	struct PoolRecord{
		Figure* instance;
		bool in_use;
		PoolRecord(Figure* object, bool in_use);
	};
	std::vector<PoolRecord> m_pool;

	ObjectPool* operator=(const ObjectPool&);
//	ObjectPool(const ObjectPool&);

public:
	ObjectPool();
	explicit ObjectPool(std::size_t);
	Figure* creatObject();
	void deleteObject(Figure* object);
	~ObjectPool();
};
//----------------------------------------
#endif // OBJECTPOOL_H
