#pragma once

#include<Siv3D.hpp>

#include<memory>

class Chicken
{
public:
	struct Coord
	{
		double x;
		double y;
	};

protected:
	Coord z_velocity;
	bool z_isEaten = false;
	bool z_isAtacked = false;
	bool z_isHitten = false;

private:
	Coord z_pos;
	bool z_isSticked = false;

public:
	virtual ~Chicken(void);

	void Initialize(const Point& pos);
	void Update(void);
	void Draw(const Point& base);
	virtual bool ShouldBeVanished(const Rect& area)const;

	virtual Circle GetHitCircle(void)const = 0;
	virtual void Hit(void) = 0;
	virtual Circle GetStickCircle(void)const = 0;
	void Sticked(void);
	void Move(Point pos);
	void Eaten(void) { z_isEaten = true; }
	virtual int Attack(void) = 0;

	bool IsSticked(void) { return z_isSticked; }
	bool IsEaten(void) { return z_isEaten; }
	virtual String GetName(void)const = 0;
	virtual int GetValue(void)const = 0;
	virtual int GetSpawnCost(void)const = 0;
	virtual std::unique_ptr<Chicken> GetNewChicken(void) = 0;

protected:
	Point GetPos(void)const;

private:
	virtual void OnInit(void) = 0;
	virtual void OnUpdate(void) = 0;
	virtual void OnDraw(const Point& pos)const = 0;
};

class CkWhite : public Chicken
{
public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"å{"; }
	int GetValue(void)const override { return 2; }
	int GetSpawnCost(void)const override { return 120; }
	std::unique_ptr<Chicken> GetNewChicken(void);

	static const Texture& Tex(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};
class CkYellow : public Chicken
{
public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"Ç–ÇÊÇ±"; }
	int GetValue(void)const override { return 2; }
	int GetSpawnCost(void)const override { return 80; }
	std::unique_ptr<Chicken> GetNewChicken(void);

	static const Texture& Tex(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};
class CkBlack : public Chicken
{
private:
	int z_count = 0;

public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"âG"; }
	int GetValue(void)const override { return 3; }
	int GetSpawnCost(void)const override { return 160; }
	std::unique_ptr<Chicken> GetNewChicken(void);

	static const Texture& Tex(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};
class CkSwallow : public Chicken
{
public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"âç"; }
	int GetValue(void)const override { return 3; }
	int GetSpawnCost(void)const override { return 160; }
	std::unique_ptr<Chicken> GetNewChicken(void);

	static const Texture& Tex(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};
class CkSwan : public Chicken
{
public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"íﬂ"; }
	int GetValue(void)const override { return 5; }
	int GetSpawnCost(void)const override { return 250; }
	std::unique_ptr<Chicken> GetNewChicken(void);

	static const Texture& Tex(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};