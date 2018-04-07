#pragma once
#include <string>
#include <map>
#include <memory>
#include "Globals.h"
using namespace std;

class IVehicle
{
public:
	IVehicle() {}
	virtual ~IVehicle() {}

	virtual string getBrand() = 0;
	virtual enumVehicleCategory getCategory() = 0;
	virtual string getLiscencePlate() = 0;

	virtual void IncreaseSeatingCapacity() = 0;
	virtual int getSeatingCapacity() = 0;

	virtual void AddPackage(enumPackages PackageType) = 0;
};


class Car : public IVehicle
{
private:
	enumVehicleCategory m_enumCategory;
	enumPackages m_enumPackage;

	string m_strBrand;
	string m_strLiscensePlate;
	int m_nMaxCapacity;

	bool m_bThridRowAdded;
public:

	Car(enumVehicleCategory VehicleCategory, const string& strBrand, const string& LiscensePlate)
		:m_enumPackage(enumPackages::STANDARD),
		m_enumCategory(VehicleCategory),
		m_strBrand(strBrand),
		m_strLiscensePlate(LiscensePlate),
		m_nMaxCapacity(5),
		m_bThridRowAdded(false)
	{
		
	}

	virtual ~Car() {}

	//getters provided incase if its needed ..
	string getBrand() { return m_strBrand; }
	enumVehicleCategory getCategory() { return m_enumCategory; }
	string getLiscencePlate() { return m_strLiscensePlate; }

	int getSeatingCapacity();	

	//increases the seating capacity by 3, assuming that it's adding a 3rd row
	void IncreaseSeatingCapacity();

	void AddPackage(enumPackages PackageType);
	
	static shared_ptr<IVehicle*> Create(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& LiscensePlate);
};

//A singleton factory to create objects. Easily scalable to create other objects in future ..
class VehicleFactory
{
private:
	//the following methods are in private to make this singleton ..
	VehicleFactory()
	{
		Register(enumVehicleType::CAR, &Car::Create);
	}

	VehicleFactory(const VehicleFactory &) { }

	VehicleFactory &operator=(const VehicleFactory &) { return *this; }

	typedef shared_ptr<IVehicle*>(*CreateVechicleFn)(enumVehicleCategory, const string&, const string&);
	map<enumVehicleType, CreateVechicleFn> m_FactoryMap;

	//scalable enough to register other vechile types like TRUCK in the future ..
	void Register(enumVehicleType VechicleType, CreateVechicleFn pfnCreate);

public:
	~VehicleFactory() { m_FactoryMap.clear(); }

	static VehicleFactory* Get();
	
	shared_ptr<IVehicle*> CreateVehicle(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& LiscensePlate);

};