#pragma once

#include<list>
#include<memory>

class Chicken;
class Ammo;
class Rancer;

class Informer
{
private:
	const std::list<std::unique_ptr<Chicken>>& z_listChicken;
	const std::list<std::unique_ptr<Ammo>>& z_listAmmo;
	const Rancer& z_rancer;

public:
	Informer(const std::list<std::unique_ptr<Chicken>>& listChicken, const std::list<std::unique_ptr<Ammo>>& listAmmo
		, const Rancer& rancer)
		: z_listChicken(listChicken), z_listAmmo(listAmmo), z_rancer(rancer) {}

	const std::list<std::unique_ptr<Chicken>>& GetListChicken(void)const { return z_listChicken; }
	const std::list<std::unique_ptr<Ammo>>& GetListAmmo(void)const { return z_listAmmo; }
	const Rancer& GetRancer(void)const { return z_rancer; }
};