//ObjectPool.cpp
#include "myHeader.h"
#include "ObjectPool.h"
#include <vector>
#include <iostream>
#include <cstdlib>

//----------------------------------------
ObjectPool::PoolRecord::PoolRecord(Shape *object = 0, bool in_use = false)
	:instance(object), in_use(in_use){}

//----------------------------------------
ObjectPool::ObjectPool(){}
//----------------------------------------
ObjectPool::ObjectPool(std::size_t size){
	try{
		for (std::size_t i = 0; i <size; ++i){
			PoolRecord record(new Shape);
			//throw(std::bad_alloc() );
			m_pool.push_back(record);
		}
	}catch(std::bad_alloc& ba){
		Vet::myError("bad_alloc for ObjectPool");
		exit(0);
	}
}
//----------------------------------------
Shape* ObjectPool::creatObject(){
	for (std::size_t i = 0; i < m_pool.size(); ++i){
		if (!m_pool[i].in_use){
			m_pool[i].in_use = true;
			std::cout<<"Выделен объект " <<m_pool[i].instance <<std::endl;//убрать
			return (m_pool[i].instance);
		}
	}
	//прошли весь пул и не нашли свободных объектов
	try{
		std::cout<<"Пулл расширен" <<std::endl;//убрать
		PoolRecord record(new Shape, true);
		//throw(std::bad_alloc() );
		m_pool.push_back(record);
		std::cout<<"Выделен объект! " <<record.instance <<std::endl;//убрать
		return (record.instance);
	}catch(std::bad_alloc& ba){
		Vet::myError("bad_alloc for ObjectPool");
		exit(0);
	}
}
//----------------------------------------
void ObjectPool::deleteObject(Shape *object){
	std::cout<<"отдали объект "<<object <<std::endl;//убрать
	for (std::size_t i = 0; i < m_pool.size(); ++i)
		if (m_pool[i].instance == object){
			m_pool[i].in_use = false;
			m_pool[i].instance->clear();
			break;
		}
}
//----------------------------------------
ObjectPool::~ObjectPool(){
	std::cout<<"деструктор " <<std::endl;//убрать
	for (std::size_t i = 0; i < m_pool.size(); ++i){
		delete m_pool[i].instance;
		m_pool[i].instance = 0;
		}
}
//----------------------------------------
