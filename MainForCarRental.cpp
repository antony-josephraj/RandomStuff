

#include "CarRentals.h"


int main()
{
	
	unique_ptr<IRentals> ptrCarRentals(new CarRentals());
	//add to the rental car collections ..
	ptrCarRentals->AddToCollections(enumVehicleCategory::SEDAN, "BMW", "LP45465");
	ptrCarRentals->AddToCollections(enumVehicleCategory::SUV, "BMW", "LP454565");
	ptrCarRentals->MaximizeSeating("LP454565"); //increases the seating capacity by 3
	ptrCarRentals->AddToCollections(enumVehicleCategory::SUV, "AUDI", "AD5790465");
	ptrCarRentals->AddToCollections(enumVehicleCategory::SEDAN, "FORD", "FD34565");
	ptrCarRentals->AddPackage("FD34565", enumPackages::SPORTS); //adds the sports package
	ptrCarRentals->MaximizeSeating("FD34565"); //does not impact the seating capacity because this is a SEDAN.

	//query the seating capacity by the license plate ...
	cout << ptrCarRentals->getSeatingCapacity("FD34565") << endl;

	return 0;

}