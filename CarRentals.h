#pragma once
#include <map>
#include <string>
#include <memory>
#include "Vehicle.h"
using namespace std;

class IRentals
{
public:
	IRentals() {}

	virtual ~IRentals() {}

	virtual void AddToCollections(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& LiscensePlate) = 0;
		
	virtual void MaximizeSeating(const string&) = 0;
	
	virtual int getSeatingCapacity(const string&) = 0;

	virtual void AddPackage(const string&, enumPackages) = 0;
};



class CarRentals : public IRentals
{
private:

	map<string, shared_ptr<IVehicle*>> vecRentalCollections;

public:

	CarRentals() {}

	void AddToCollections(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& strLiscensePlate);	

	void MaximizeSeating(const string& strLiscensePlate);	

	int getSeatingCapacity(const string& strLiscensePlate);	

	void AddPackage(const string& strLiscensePlate, enumPackages PackageType);	

};