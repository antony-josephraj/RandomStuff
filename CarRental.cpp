#include "CarRentals.h"

void CarRentals::AddToCollections(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& strLiscensePlate)
{
	shared_ptr<IVehicle*> ptrVehicle = VehicleFactory::Get()->CreateVehicle(enumVehicleCategory, strBrand, strLiscensePlate);
	vecRentalCollections[strLiscensePlate] = ptrVehicle;

}

void CarRentals::MaximizeSeating(const string& strLiscensePlate)
{
	map<string, shared_ptr<IVehicle*>>::iterator iter = vecRentalCollections.find(strLiscensePlate);
	if (iter != vecRentalCollections.end())
	{
		(*iter->second)->IncreaseSeatingCapacity();
	}
}

int CarRentals::getSeatingCapacity(const string& strLiscensePlate)
{
	int bRetVal = 0;
	map<string, shared_ptr<IVehicle*>>::iterator iter = vecRentalCollections.find(strLiscensePlate);
	if (iter != vecRentalCollections.end())
	{
		bRetVal = (*iter->second)->getSeatingCapacity();
	}
	return bRetVal;
}

void CarRentals::AddPackage(const string& strLiscensePlate, enumPackages PackageType)
{
	map<string, shared_ptr<IVehicle*>>::iterator iter = vecRentalCollections.find(strLiscensePlate);
	if (iter != vecRentalCollections.end())
	{
		(*iter->second)->IncreaseSeatingCapacity();
	}
}