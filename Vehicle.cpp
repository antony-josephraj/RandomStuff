#include "Vehicle.h"
using namespace std;

int Car::getSeatingCapacity()
{
	return m_nMaxCapacity;
}

void Car::IncreaseSeatingCapacity()
{
	if ((m_enumCategory == enumVehicleCategory::SUV) && (!m_bThridRowAdded))
	{
		m_nMaxCapacity += 3;
		m_bThridRowAdded = true;
	}
}
void Car::AddPackage(enumPackages PackageType)
{
	if (m_enumCategory == enumVehicleCategory::SUV)
	{
		m_enumPackage = PackageType;
	}

}
 shared_ptr<IVehicle*> Car::Create(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& LiscensePlate)
{
	return make_shared<IVehicle*>(new Car(enumVehicleCategory, strBrand, LiscensePlate));
}



 //factory methods starts here ....

 void VehicleFactory::Register(enumVehicleType VechicleType, CreateVechicleFn pfnCreate)
 {
	 m_FactoryMap[VechicleType] = pfnCreate;
 }

 VehicleFactory* VehicleFactory::Get()
 {
	 static VehicleFactory instance;
	 return &instance;
 }

 shared_ptr<IVehicle*> VehicleFactory::CreateVehicle(enumVehicleCategory enumVehicleCategory, const string& strBrand, const string& LiscensePlate)
 {
	 map<enumVehicleType, CreateVechicleFn>::iterator it = m_FactoryMap.find(enumVehicleType::CAR);
	 if (it != m_FactoryMap.end())
	 {
		 //invokes the create of the corresponding object (car in this case)
		 return it->second(enumVehicleCategory, strBrand, LiscensePlate);
	 }

	 return NULL;
 }