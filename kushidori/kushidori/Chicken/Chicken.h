#pragma once

#include<Siv3D.hpp>

#include<memory>

class Chicken
{
protected:
	Point z_velocity;
	bool z_isEaten = false;
	bool z_isAtacked = false;

private:
	Point z_pos;
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
	virtual std::unique_ptr<Chicken> GetNewChicken(void) = 0;

protected:
	Point GetPos(void)const { return z_pos; }

private:
	virtual void OnInit(void) = 0;
	virtual void OnUpdate(void) = 0;
	virtual void OnDraw(const Point& pos)const = 0;
};

class White : public Chicken
{
public:
	Circle GetHitCircle(void)const override;
	void Hit(void)override;
	Circle GetStickCircle(void)const override;
	int Attack(void)override;

	String GetName(void)const override { return L"White"; }
	int GetValue(void)const override { return 2; }
	std::unique_ptr<Chicken> GetNewChicken(void);

private:
	void OnInit(void)override;
	void OnUpdate(void)override;
	void OnDraw(const Point& pos)const override;
};